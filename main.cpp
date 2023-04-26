/*
This code uses the Qt framework to create the GUI components. The MyWidget class creates the input box, output box, processing button, and list widget. The processInput function is called when the processing button is clicked. It reverses the input string and displays it in the output box. It also adds the original input and the reversed output to the list widget, keeping only the last 10 entries. Finally, the main function creates an instance of the MyWidget class and shows it.

Note that you'll need to install the Qt framework and link against the appropriate libraries to compile and run this code. Also, this is just a simple example, and there are many ways to improve the functionality and usability of this application.
*/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>

class MyWidget : public QWidget {
public:
    MyWidget() {
        // Input box
        inputBox = new QLineEdit(this);

        // Output box
        outputBox = new QTextEdit(this);
        outputBox->setReadOnly(true);

        // Processing button
        processButton = new QPushButton("Process", this);
        connect(processButton, SIGNAL(clicked()), this, SLOT(processInput()));

        // List widget
        listWidget = new QListWidget(this);

        // Layout
        QVBoxLayout *mainLayout = new QVBoxLayout;
        QHBoxLayout *inputLayout = new QHBoxLayout;
        inputLayout->addWidget(inputBox);
        inputLayout->addWidget(processButton);
        mainLayout->addLayout(inputLayout);
        mainLayout->addWidget(outputBox);
        mainLayout->addWidget(listWidget);
        setLayout(mainLayout);

        // Set window properties
        setWindowTitle("My Application");
        resize(400, 400);
    }

private slots:
    void processInput() {
        QString input = inputBox->text();
        QString output = input.reversed();
        outputBox->setText(output);
        addToList(input, output);
    }

private:
    QLineEdit *inputBox;
    QTextEdit *outputBox;
    QPushButton *processButton;
    QListWidget *listWidget;
    std::vector<std::pair<QString, QString>> processedInputs;

    void addToList(const QString& input, const QString& output) {
        // Add to list widget
        QString reversedInput = input.reversed();
        QString reversedOutput = output.reversed();
        processedInputs.push_back(std::make_pair(reversedInput, reversedOutput));
        listWidget->addItem(QString("%1 -> %2").arg(reversedInput).arg(reversedOutput));

        // Keep only the last 10 entries
        if (processedInputs.size() > 10) {
            processedInputs.erase(processedInputs.begin());
            QListWidgetItem *item = listWidget->takeItem(0);
            delete item;
        }
    }
};

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MyWidget widget;
    widget.show();
    return app.exec();
}
