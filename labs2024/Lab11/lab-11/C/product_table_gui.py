import sys

from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QApplication, QMainWindow, QVBoxLayout
from PyQt6.QtWidgets import QPushButton, QTableView, QWidget

from controller import Controller
from product import Product
from product_table_model import ProductTableModel
from add_product_gui import AddProductGUI
from list_product_gui import ListProductGUI

class ProductTableGUI(QMainWindow):

    def __init__(self):
        super().__init__()
        self.controller = Controller()
        self.setWindowTitle("Products")
        self.resize(600, 400)

        # add sub windows
        self.add_product_gui = AddProductGUI(self.controller, parent=self)
        self.list_product_gui = ListProductGUI(self.controller)

        self.product_table = QTableView()

        self.product_model = ProductTableModel(self.controller)
        self.product_table.setModel(self.product_model)

        add_button = QPushButton("Add Product")
        add_button.clicked.connect(self.add_button_clicked)
    
        # connect the double click signal to allow storing the current product's code
        self.current_product_code = None
        self.product_table.doubleClicked.connect(self.list_product_requested)

        layout = QVBoxLayout()
        layout.addWidget(self.product_table)
        layout.addWidget(add_button)

        widget = QWidget()
        widget.setLayout(layout)
        self.setCentralWidget(widget)
        self.refresh_table()

    def refresh_table(self):
        # TODO: Bring the code from the refresh_button_clicked() from the
        # previous exercise, and add it here.

        # Refresh product data in the model
        self.product_model.refresh_data()

        # Adjust the column widths to fit the content
        self.product_table.resizeColumnsToContents()

        # Enable the table for interaction
        self.product_table.setEnabled(True)





    def add_button_clicked(self):
        # TODO: After you fix the AddProductGUI class,add code here to
        # show that secondary window.

        # Show the AddProductGUI window
        self.add_product_gui.show()
        
        


    def list_product_requested(self):
        ''' store the current product's code when the user selects a row '''
        index = self.product_table.selectionModel().currentIndex()
        self.current_product_code = int(index.sibling(index.row(), 0).data())
        # Notice that the selected product's code is passed to the new
        # window's list_product() method, which is needed to search the
        # correct product, and list it in the new window.
        self.list_product_gui.list_product(self.current_product_code)
        self.list_product_gui.show()

    def closeEvent(self, event):
        ''' close all the secondary windows when this window is closed '''
        for window in QApplication.topLevelWidgets():
            window.close()

def main():
    app = QApplication(sys.argv)
    window = ProductTableGUI()
    window.show()
    app.exec()


if __name__ == '__main__':
    main()
