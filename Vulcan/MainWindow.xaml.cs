using ManagedVulcanCore;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using System;
using System.Diagnostics;
using System.Threading.Tasks;
using Windows.Storage.Pickers;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace Vulcan
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainWindow : Window
    {

        private string currentSelectFile = "";
        private string fileName = "";
        private ManagedVulcanCore.ManagedFStream m_stream;
        private ManagedVulcanCore.ManagedForge m_forge;

        public MainWindow()
        {
            this.InitializeComponent();
            this.Title = "Vulcan";
        }

        private async void HandleMenuBarClick(object sender, RoutedEventArgs e)
        {
            var selectedFlyoutItem = sender as MenuFlyoutItem;
            Debug.WriteLine(selectedFlyoutItem.Name);
            switch (selectedFlyoutItem.Name)
            {
                case "VMenuBarOpenFile":
                    await OpenForgeFile();
                    break;
                case "VMenuBarExit":
                    Environment.Exit(0);
                    break;
                default:
                    break;
            }
        }

        private async Task OpenForgeFile()
        {
            await SelectFileAsync();
            LoadForge();
        }

        private async Task SelectFileAsync()
        {
            // Clear previous returned file name, if it exists, between iterations of this scenario
            //OutputTextBlock.Text = "";

            // Create a file picker
            var openPicker = new Windows.Storage.Pickers.FileOpenPicker();

            // Retrieve the window handle (HWND) of the current WinUI 3 window.
            //var window = WindowHelper.GetWindowForElement(this);
            var hWnd = WinRT.Interop.WindowNative.GetWindowHandle(this);

            // Initialize the file picker with the window handle (HWND).
            WinRT.Interop.InitializeWithWindow.Initialize(openPicker, hWnd);

            // Set options for your file picker
            openPicker.ViewMode = PickerViewMode.List;
            openPicker.FileTypeFilter.Add(".FORGE");

            // Open the picker for the user to pick a file
            var file = await openPicker.PickSingleFileAsync();
            if (file != null)
            {
                //PickAFileOutputTextBlock.Text = "Picked file: " + file.Name;
                Debug.WriteLine($"Picked file: {file.Name}");
                currentSelectFile = file.Path;
                fileName = file.Name;
            }
            else
            {
                //PickAFileOutputTextBlock.Text = "Operation cancelled.";
                Debug.WriteLine("Operation cancelled");
            }
        }

        private TextBlock CreateTextBlock(String text)
        {
            var block = new TextBlock();
            block.Text = text;
            return block;
        }

        private void LoadForge()
        {
            VulcanMainNode.IsExpanded = false;

            m_stream?.Dispose();
            m_forge?.Dispose();

            m_stream = new ManagedFStream(currentSelectFile);
            m_forge = new ManagedForge(m_stream);
            Debug.WriteLine($"Loaded file {currentSelectFile} with {m_forge.entries.Length} entries");

            VulcanMainNode.Content = fileName;

            VulcanMainNode.Children.Clear();
            for (var i = 0; i < m_forge.entries.Length; i++)
            {
                VulcanMainNode.Children.Add(new TreeViewNode() { Content = "0x" + m_forge.entries[i].Uid.ToString("X") + " ; " + m_forge.entryMetadatas[i].Name });
            }
        }
    }
}
