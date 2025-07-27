-- init.lua - Minimal Neovim config with custom LSP server (Modern API)
vim.pack.add{
  { src = 'https://github.com/neovim/nvim-lspconfig' },
  { src = 'https://github.com/folke/snacks.nvim' },
}
-- Enable LSP logging (optional, for debugging)
vim.lsp.set_log_level("debug")

-- Configure your custom LSP server using the modern API
vim.lsp.config['custom-lsp'] = {
  cmd = { '/home/tera8/proj/cpp-lsp/build/standalone/Greeter' },
  filetypes = { 'cpp', 'c', 'h', 'hpp' },
  root_markers = { { 'CMakeLists.txt', 'Makefile' }, '.git' },
  settings = {},
  on_attach = function(client, bufnr)
    print("LSP server '" .. client.name .. "' started and attached to buffer " .. bufnr)
    
    -- Set up keymaps for this buffer
    local opts = { buffer = bufnr }
    vim.keymap.set('n', 'gd', vim.lsp.buf.definition, opts)
    vim.keymap.set('n', 'K', vim.lsp.buf.hover, opts)
    vim.keymap.set('n', '<leader>rn', vim.lsp.buf.rename, opts)
    vim.keymap.set('n', '<leader>ca', vim.lsp.buf.code_action, opts)
  end,
  on_error = function(err)
    print("LSP server error: " .. vim.inspect(err))
  end,
  handlers = {
    ["window/showMessage"] = function(err, method, params)
      print("LSP message: " .. params.message)
    end,
    ["window/logMessage"] = function(err, method, params)
      print("LSP log: " .. params.message)
    end,
  },
}

-- Enable the LSP configuration
print("Enabling LSP configuration: custom-lsp")
local ok, err = pcall(vim.lsp.enable, 'custom-lsp')
if ok then
  print("LSP configuration enabled successfully")
else
  print("Failed to enable LSP configuration: " .. tostring(err))
  -- Check if the executable exists
  local cmd = '/home/tera8/proj/cpp-lsp/build/standalone/Greeter'
  if vim.fn.executable(cmd) == 0 then
    print("LSP executable not found or not executable: " .. cmd)
  end
end

-- Basic options
vim.opt.number = true
vim.opt.expandtab = true
vim.opt.shiftwidth = 2
vim.opt.tabstop = 2

-- Custom LspInfo command for additional debugging
vim.api.nvim_create_user_command('MyLspInfo', function()
  local clients = vim.lsp.get_clients()
  if #clients == 0 then
    print("No active LSP clients")
    return
  end
  
  for _, client in ipairs(clients) do
    print("Client: " .. client.name .. " (ID: " .. client.id .. ")")
    print("  Attached buffers: " .. vim.inspect(vim.tbl_keys(client.attached_buffers)))
    print("  Server capabilities: " .. vim.inspect(client.server_capabilities))
  end
end, {})

-- Custom command to test workspace/symbol with raw output
vim.api.nvim_create_user_command('TestWorkspaceSymbols', function(opts)
  local query = opts.args or ""
  local clients = vim.lsp.get_clients({ bufnr = 0 })
  
  if #clients == 0 then
    print("No LSP clients attached to current buffer")
    return
  end
  
  local client = clients[1]
  print("Requesting workspace symbols with query: '" .. query .. "'")
  
  local params = { query = query }
  
  client.request('workspace/symbol', params, function(err, result, ctx)
    if err then
      print("Error: " .. vim.inspect(err))
      return
    end
    
    print("Raw workspace/symbol response:")
    print(vim.inspect(result))
    
    if result and #result > 0 then
      print("\nFound " .. #result .. " symbols:")
      for i, symbol in ipairs(result) do
        local location = ""
        if symbol.location and symbol.location.uri then
          location = " in " .. symbol.location.uri
        end
        print(i .. ". " .. symbol.name .. " (" .. (symbol.kind or "unknown") .. ")" .. location)
      end
    else
      print("No symbols found")
    end
  end, 0)
end, { nargs = '?' })

-- Custom command to check if workspace/symbol is supported
vim.api.nvim_create_user_command('CheckWorkspaceSymbolSupport', function()
  local clients = vim.lsp.get_clients({ bufnr = 0 })
  
  if #clients == 0 then
    print("No LSP clients attached to current buffer")
    return
  end
  
  for _, client in ipairs(clients) do
    local supports = client.supports_method('workspace/symbol')
    print("Client '" .. client.name .. "' supports workspace/symbol: " .. tostring(supports))
    
    if client.server_capabilities.workspaceSymbolProvider then
      print("  workspaceSymbolProvider: " .. vim.inspect(client.server_capabilities.workspaceSymbolProvider))
    else
      print("  workspaceSymbolProvider: not supported")
    end
  end
end, {})
