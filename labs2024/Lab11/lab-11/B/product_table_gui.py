import sys

from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QApplication, QMainWindow, QVBoxLayout
from PyQt6.QtWidgets import QPushButton, QTableView, QWidget

from controller import Controller
from product import Product
from product_table_model import ProductTableModel

class ProductTableGUI(QMainWindow):

    def __init__(self):
        super().__init__()
        self.controller = Controller()
        self.setWindowTitle("Products")
        self.resize(600, 400)

        self.product_table = QTableView()

        self.product_model = ProductTableModel(self.controller)
        self.product_table.setModel(self.product_model)

        refresh_button = QPushButton("Refresh")
        refresh_button.clicked.connect(self.refresh_button_clicked)
        clear_button = QPushButton("Clear")
        clear_button.clicked.connect(self.clear_button_clicked)

        layout = QVBoxLayout()
        layout.addWidget(self.product_table)
        layout.addWidget(refresh_button)
        layout.addWidget(clear_button)

        widget = QWidget()
        widget.setLayout(layout)
        self.setCentralWidget(widget)
        self.refresh_button_clicked()


    def refresh_button_clicked(self):
        # TODO: After you complete the refresh_data() method in the table model 
        # class, call this method, fix the product description's column width to
        # better use the window size, and make the product table editable.

        # Refresh product data in the model
        self.product_model.refresh_data()

        # Adjust the column widths to fit the content
        self.product_table.resizeColumnsToContents()

        # Make the product table editable
        self.product_table.setEnabled(True)



    def clear_button_clicked(self):
        # TODO: call the reset() method in the table model and disable edits in
        #  the product table. (Do you understand why you should disable it?).

        # Clear product data in the model
        self.product_model.reset()

        # Disable the product table to prevent edits
        self.product_table.setEnabled(False)






def main():
    app = QApplication(sys.argv)
    window = ProductTableGUI()
    window.show()
    app.exec()

if __name__ == '__main__':
    main()
