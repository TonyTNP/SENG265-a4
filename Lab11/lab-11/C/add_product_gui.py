import sys

from PyQt6.QtWidgets import QApplication, QMainWindow, QWidget
from PyQt6.QtWidgets import QLabel, QLineEdit, QPushButton, QMessageBox
from PyQt6.QtWidgets import QGridLayout, QVBoxLayout, QHBoxLayout
from PyQt6.QtCore import Qt

from controller import Controller, IllegalOperationException

class AddProductGUI(QMainWindow):
    def __init__(self, controller, parent):
        super().__init__()
        self.controller = controller
        self.parent = parent
        self.setWindowTitle("Add Product")

        layout1 = QGridLayout()

        label_code = QLabel("Product Code")
        self.text_code = QLineEdit()
        self.text_code.setInputMask('00000000')
        label_description = QLabel("Description")
        self.text_description = QLineEdit()
        label_price = QLabel("Price")
        self.text_price = QLineEdit()

        layout1.addWidget(label_code, 0, 0)
        layout1.addWidget(self.text_code, 0, 1)
        layout1.addWidget(label_description, 1, 0)
        layout1.addWidget(self.text_description, 1, 1)
        layout1.addWidget(label_price, 2, 0)
        layout1.addWidget(self.text_price, 2, 1)

        layout2 = QHBoxLayout()

        self.button_clear = QPushButton("Clear")
        self.button_create = QPushButton("Add")
        self.button_close = QPushButton("Close")
        layout2.addWidget(self.button_clear)
        layout2.addWidget(self.button_create)
        layout2.addWidget(self.button_close)

        layout3 = QVBoxLayout()

        top_widget = QWidget()
        top_widget.setLayout(layout1)
        bottom_widget = QWidget()
        bottom_widget.setLayout(layout2)
        layout3.addWidget(top_widget)
        layout3.addWidget(bottom_widget)
        widget = QWidget()
        widget.setLayout(layout3)

        self.setCentralWidget(widget)

        # define widgets' initial state
        self.text_code.setEnabled(True)
        self.text_description.setEnabled(True)
        self.text_price.setEnabled(True)
        self.button_clear.setEnabled(True)
        self.button_create.setEnabled(False)
        self.button_close.setEnabled(True)

        # handle text change to enable/disable the create button
        self.text_code.textChanged.connect(self.product_text_changed)
        self.text_description.textChanged.connect(self.product_text_changed)
        self.text_price.textChanged.connect(self.product_text_changed)

        # connect the buttons' clicked signals to the slots below
        self.button_clear.clicked.connect(self.clear_button_clicked)
        self.button_create.clicked.connect(self.create_button_clicked)
        self.button_close.clicked.connect(self.close_button_clicked)

    def product_text_changed(self):
        if self.text_code.text() and self.text_description.text() and self.text_price.text():
            self.button_create.setEnabled(True)
        else:
            self.button_create.setEnabled(False)

    def clear_button_clicked(self):
        ''' clear the fields '''
        # TODO: Clear all the QLineEdits' text.

        self.text_code.clear()
        self.text_description.clear()
        self.text_price.clear()


    def create_button_clicked(self):
        ''' add new product '''
        try:
            # TODO: Recover the product data from the QLineEdits and store them
            # in local variables. You may have to do some conversions.
            # Then, call controller.create_product() to add the new product.
            # After successful creation, show an information message of success,
            # close this Add Products window.

            # Retrieve input values
            code = self.text_code.text()
            description = self.text_description.text()

            # Ensure price is a valid float
            try:
                price = float(self.text_price.text())
            except ValueError:
                QMessageBox.warning(self, "Invalid Input", "Price must be a valid number.")
                return

            # Add the product using the controller
            self.controller.create_product(code, description, price)

            # Show a success message
            QMessageBox.information(self, "Success", f"Product '{description}' created successfully!")


            # After a product is created, the original parent window with the table 
            # needs to be updated, refreshing the table data from the products' storage.   
            self.parent.refresh_table()
            self.close_button_clicked()

        except IllegalOperationException:
            # TODO: Show a message with an error when adding a product with an existing code.
            # Show a message if a product with the same code already exists
            QMessageBox.warning(self, "Error", f"A product with code '{code}' already exists.")



    def close_button_clicked(self):
        ''' 'close add product window '''
        # Notice that it is important to clear the QLineEdits when this window is
        # closed, so they will come back clean when the window is reopened.
        self.clear_button_clicked()
        self.hide()

    def closeEvent(self, event):
        self.close_button_clicked()

         #Here is the tester for C: 
        # python product_table_gui.py
