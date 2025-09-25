#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OBSERVERS 10

typedef struct Observer Observer;
typedef struct Subject Subject;

struct Observer {
    void (*update)(Observer* self, Subject* subject);
    char* name;
};

struct Subject {
    Observer* observers[MAX_OBSERVERS];
    int observer_count;
    int state;
};

void subject_attach(Subject* subject, Observer* observer) {
    if (subject->observer_count < MAX_OBSERVERS) {
        subject->observers[subject->observer_count++] = observer;
        printf("Observer %s attached\n", observer->name);
    }
}

void subject_detach(Subject* subject, Observer* observer) {
    for (int i = 0; i < subject->observer_count; i++) {
        if (subject->observers[i] == observer) {
            for (int j = i; j < subject->observer_count - 1; j++) {
                subject->observers[j] = subject->observers[j + 1];
            }
            subject->observer_count--;
            printf("Observer %s detached\n", observer->name);
            break;
        }
    }
}

void subject_notify(Subject* subject) {
    printf("Notifying %d observers about state change to %d\n",
           subject->observer_count, subject->state);
    for (int i = 0; i < subject->observer_count; i++) {
        subject->observers[i]->update(subject->observers[i], subject);
    }
}

void subject_set_state(Subject* subject, int new_state) {
    subject->state = new_state;
    subject_notify(subject);
}

void display_observer_update(Observer* self, Subject* subject) {
    printf("Display %s: Temperature changed to %d°C\n", self->name, subject->state);
}

void alert_observer_update(Observer* self, Subject* subject) {
    if (subject->state > 30) {
        printf("Alert %s: WARNING! High temperature: %d°C\n", self->name, subject->state);
    } else if (subject->state < 0) {
        printf("Alert %s: WARNING! Freezing temperature: %d°C\n", self->name, subject->state);
    }
}

Observer* create_display_observer(const char* name) {
    Observer* obs = malloc(sizeof(Observer));
    obs->update = display_observer_update;
    obs->name = malloc(strlen(name) + 1);
    strcpy(obs->name, name);
    return obs;
}

Observer* create_alert_observer(const char* name) {
    Observer* obs = malloc(sizeof(Observer));
    obs->update = alert_observer_update;
    obs->name = malloc(strlen(name) + 1);
    strcpy(obs->name, name);
    return obs;
}

void destroy_observer(Observer* obs) {
    if (obs) {
        free(obs->name);
        free(obs);
    }
}

Subject* create_subject() {
    Subject* subject = malloc(sizeof(Subject));
    subject->observer_count = 0;
    subject->state = 20; // Default temperature
    return subject;
}

void destroy_subject(Subject* subject) {
    free(subject);
}

int main() {
    Subject* weather_station = create_subject();

    Observer* display1 = create_display_observer("Display1");
    Observer* display2 = create_display_observer("Display2");
    Observer* alert_system = create_alert_observer("AlertSystem");

    subject_attach(weather_station, display1);
    subject_attach(weather_station, display2);
    subject_attach(weather_station, alert_system);

    printf("\n--- Temperature Changes ---\n");
    subject_set_state(weather_station, 25);
    printf("\n");

    subject_set_state(weather_station, 35);
    printf("\n");

    subject_detach(weather_station, display1);
    subject_set_state(weather_station, -5);

    destroy_observer(display1);
    destroy_observer(display2);
    destroy_observer(alert_system);
    destroy_subject(weather_station);

    return 0;
}