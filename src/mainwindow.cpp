
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_scene = new NGLScene(this);
    m_ui->m_mainWindowGridLayout->addWidget(m_scene, 0,0,9,3);
    m_scene->show();

    connect(m_ui->m_clear_boids_btn, SIGNAL(clicked(bool)), m_scene, SLOT(clear_boids()));
    connect(m_ui->m_alignment_checkBox, &QCheckBox::clicked,
            [=]()
            {
                m_scene->set_alignment(m_ui->m_alignment_checkBox->isChecked());
            });
    connect(m_ui->m_separation_checkBox, &QCheckBox::clicked,
            [=]()
            {
                m_scene->set_separation(m_ui->m_separation_checkBox->isChecked());
            });
    connect(m_ui->m_cohesion_checkBox, &QCheckBox::clicked,
            [=]()
            {
                m_scene->set_cohesion(m_ui->m_cohesion_checkBox->isChecked());
            });

    connect(m_ui->m_addBoids_btn, &QPushButton::clicked,
            [=]()
            {
                m_scene->add_boids(m_ui->m_numParticles_spinBox->value());
            });
    connect(m_ui->m_reset_btn, &QPushButton::clicked,
            [=]()
            {
                m_ui->m_alignment_checkBox->setChecked(false);
                m_ui->m_cohesion_checkBox->setChecked(false);
                m_ui->m_separation_checkBox->setChecked(false);

                m_ui->m_boidSize_spinBox->setValue(5);
                m_ui->m_threshold_spinBox->setValue(1.0);
                m_ui->m_maxForce_spinBox->setValue(5.0);
                m_ui->m_speedLoss_spinBox->setValue(0.2);
                m_ui->m_deltaTime_spinBox->setValue(0.03);

                m_ui->m_cohesion_spinBox->setValue(0.3);
                m_ui->m_alignment_spinBox->setValue(0.1);
                m_ui->m_separation_spinBox->setValue(2.3);

                m_ui->m_tankPosx_spinBox->setValue(0.0);
                m_ui->m_tankPosy_spinBox->setValue(0.0);
                m_ui->m_tankPosz_spinBox->setValue(0.0);

                m_ui->m_tankRadiusx_spinBox->setValue(6.0);
                m_ui->m_tankRadiusy_spinBox->setValue(6.0);
                m_ui->m_tankRadiusz_spinBox->setValue(6.0);

                m_ui->m_emitx_spinBox->setValue(2.0);
                m_ui->m_emity_spinBox->setValue(2.0);
                m_ui->m_emitz_spinBox->setValue(4.0);

                m_ui->m_gravity_spinBox->setValue(-5.5);

                m_scene->set_defaults();
            });

    connect(m_ui->m_cohesion_spinBox, SIGNAL(valueChanged(double)), m_scene, SLOT(set_cohesion_factor(double)));
    connect(m_ui->m_alignment_spinBox, SIGNAL(valueChanged(double)), m_scene, SLOT(set_alignment_factor(double)));
    connect(m_ui->m_separation_spinBox, SIGNAL(valueChanged(double)), m_scene, SLOT(set_separation_factor(double)));

    connect(m_ui->m_threshold_spinBox, SIGNAL(valueChanged(double)), m_scene, SLOT(set_threshold(double)));
    connect(m_ui->m_boidSize_spinBox, SIGNAL(valueChanged(int)), m_scene, SLOT(set_boid_size(int)));

    connect(m_ui->m_maxForce_spinBox, SIGNAL(valueChanged(double)), m_scene, SLOT(set_force(double)));
    connect(m_ui->m_speedLoss_spinBox, SIGNAL(valueChanged(double)), m_scene, SLOT(set_speed_loss(double)));
    connect(m_ui->m_deltaTime_spinBox, SIGNAL(valueChanged(double)), m_scene, SLOT(set_delta_time(double)));

    connect(m_ui->m_tankPosx_spinBox, SIGNAL(valueChanged(double)), m_scene, SLOT(set_tank_pos_x(double)));
    connect(m_ui->m_tankPosy_spinBox, SIGNAL(valueChanged(double)), m_scene, SLOT(set_tank_pos_y(double)));
    connect(m_ui->m_tankPosz_spinBox, SIGNAL(valueChanged(double)), m_scene, SLOT(set_tank_pos_z(double)));

    connect(m_ui->m_tankRadiusx_spinBox, SIGNAL(valueChanged(double)), m_scene, SLOT(set_tank_rad_x(double)));
    connect(m_ui->m_tankRadiusy_spinBox, SIGNAL(valueChanged(double)), m_scene, SLOT(set_tank_rad_y(double)));
    connect(m_ui->m_tankRadiusz_spinBox, SIGNAL(valueChanged(double)), m_scene, SLOT(set_tank_rad_z(double)));

    connect(m_ui->m_emitx_spinBox, SIGNAL(valueChanged(double)), m_scene, SLOT(set_emit_dir_x(double)));
    connect(m_ui->m_emity_spinBox, SIGNAL(valueChanged(double)), m_scene, SLOT(set_emit_dir_y(double)));
    connect(m_ui->m_emitz_spinBox, SIGNAL(valueChanged(double)), m_scene, SLOT(set_emit_dir_z(double)));

    connect(m_ui->m_gravity_spinBox, SIGNAL(valueChanged(double)), m_scene, SLOT(set_gravity(double)));
}

MainWindow::~MainWindow()
{
    delete m_ui;
    delete m_scene;
}


