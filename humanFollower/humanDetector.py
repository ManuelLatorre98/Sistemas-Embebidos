import mediapipe as mp
import cv2

class HumanDetector():
  def __init__(self,
               model_complexity=0,
                static_image_mode=False,
                min_detection_confidence=0.5,
                min_tracking_confidence=0.5):
    self.model_complexity = model_complexity
    self.static_image_mode = static_image_mode
    self.min_detection_confidence = min_detection_confidence
    self.min_tracking_confidence = min_tracking_confidence
    self.mp_pose = mp.solutions.pose
    self.mp_drawing = mp.solutions.drawing_utils

    self.pose = self.mp_pose.Pose(model_complexity=0,
                     static_image_mode=False,
                     min_detection_confidence=0.5,
                     min_tracking_confidence=0.5)
    self.distance = 0
    self.angle_degrees=0

  def normalize(self, landmark_x, landmark_y):
    return int(landmark_x * self.img_width), int(landmark_y * self.img_height)

  def findLandMarks(self, img):
    #BGR to RGB
    rgb_img= cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

    self.img_height, self.img_width, _ = img.shape

    #Process the img with pose process
    self.result = self.pose.process(rgb_img)
    self.landmarks = self.result.pose_landmarks
    #If exists landmarks draw it
    if self.landmarks:
      self.mp_drawing.draw_landmarks(img, 
                                self.landmarks,
                                self.mp_pose.POSE_CONNECTIONS )
    return img
  
  def draw_bounding_box(self, img):
    if self.landmarks:
      min_x, min_y = self.img_height, self.img_width 
      max_x, max_y = 0, 0 # starts with minimal values

      for landmark in self.landmarks.landmark:
        # Convert the points normalized to pixels coords
        x, y =self.normalize(landmark.x, landmark.y)

        min_x = min(min_x, x)
        min_y = min(min_y, y)
        max_x = max(max_x, x)
        max_y = max(max_y, y)

        if self.landmarks.landmark[self.mp_pose.PoseLandmark.NOSE]:
            nose = self.landmarks.landmark[self.mp_pose.PoseLandmark.NOSE]
            nose_x, nose_y = self.normalize(nose.x, nose.y)

            # Ajustar el límite superior considerando la nariz
            min_y = min(min_y, nose_y - 60)  # Ajusta el valor para incluir la frente

      cv2.rectangle(img, (min_x, min_y), (max_x,max_y), (0,255,0),2)
      label = f'Distancia: {self.distance:.0f}cm'
      label_position = (min_x-1, min_y-6)  # Ajusta la posición según sea necesario

      # Calcular el tamaño del texto para dibujar un rectángulo detrás
      (text_width, text_height), baseline = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.5, 1)
      
      # Dibujar el fondo del texto
      cv2.rectangle(img, (label_position[0], label_position[1] - text_height - baseline),
                    (label_position[0] + text_width, label_position[1]+7), (50, 50, 0), cv2.FILLED)

      # Dibujar la etiqueta
      cv2.putText(img, label, label_position, cv2.FONT_HERSHEY_SIMPLEX, 0.5, (210,210,210), 2)

      # SEGUNDA LABEL
      
      label = f'{self.angle_degrees:.0f}g'
      (text_width, text_height), baseline = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.5, 1)
      label_position_max = (max_x-text_width, min_y-6)  # Ajusta la posición según sea necesario
      cv2.rectangle(img, (label_position_max[0], label_position_max[1] - text_height - baseline),
                    (label_position_max[0]+ text_width, label_position_max[1] +7), (50, 50, 0), cv2.FILLED)

  
      # Dibujar la etiqueta
      cv2.putText(img, label, label_position_max, cv2.FONT_HERSHEY_SIMPLEX, 0.5, (210,210,210), 2)
    return img

  def check_on_his_back(self):
    if self.landmarks:
      left_shoulder = self.landmarks.landmark[self.mp_pose.PoseLandmark.LEFT_SHOULDER]
      right_shoulder = self.landmarks.landmark[self.mp_pose.PoseLandmark.RIGHT_SHOULDER]
      nose = self.landmarks.landmark[self.mp_pose.PoseLandmark.NOSE]

      left_shoulder_x, left_shoulder_y = self.normalize(left_shoulder.x, left_shoulder.y)
      right_shoulder_x, right_shoulder_y = self.normalize(right_shoulder.x, right_shoulder.y)
      nose_x,nose_y = self.normalize(nose.x, nose.y)

      if left_shoulder_y > nose_y and right_shoulder_y > nose_y:
        if abs(left_shoulder_x - right_shoulder_x) > 50:
          return "DE ESPALDAS"
      return "DE FRENTE"

    return "SIN RESULTADOS"  
  
  def calculate_distance(self, img, person_height_mm=1700, focal_length_mm=20): #retorna en cm
    offset = 160 #cm ajustar segun camara
    if self.landmarks:
      nose = self.landmarks.landmark[self.mp_pose.PoseLandmark.NOSE]
      left_ankle = self.landmarks.landmark[self.mp_pose.PoseLandmark.LEFT_ANKLE]
      right_ankle = self.landmarks.landmark[self.mp_pose.PoseLandmark.RIGHT_ANKLE]
      _,nose_y = self.normalize(nose.x,nose.y)
      ankles_y = (self.normalize(left_ankle.x, left_ankle.y)[1] + self.normalize(right_ankle.x, right_ankle.y)[1]) / 2

      height_in_pixels = abs(nose_y - ankles_y)

      self.distance= ((person_height_mm * focal_length_mm) / height_in_pixels)+offset if height_in_pixels > 0 else None
      return (self.distance)
    return None
  
  def calculate_angle_from_center(self, img, fov=60):
    if(self.landmarks):
      nose = self.landmarks.landmark[self.mp_pose.PoseLandmark.NOSE]
      nose_x, _ = self.normalize(nose.x, nose.y)
      img_center_x = self.img_width/2
      displacement = nose_x - img_center_x
      angle_per_pixel = fov / self.img_width
      self.angle_degrees = displacement * angle_per_pixel
      return self.angle_degrees
    return 0


      
      
    

  