<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $nom = htmlspecialchars($_POST['nom']);
    $prenom = htmlspecialchars($_POST['prenom']);
    $ville = htmlspecialchars($_POST['ville']);
    $code_postal = htmlspecialchars($_POST['code_postal']);
    $email = filter_var($_POST['email'], FILTER_SANITIZE_EMAIL);
    $telephone = htmlspecialchars($_POST['telephone']);
    $message = htmlspecialchars($_POST['message']);

    $to = 'votre.email@exemple.com';
    $subject = "Nouveau message de contact - Formation IA";
    $body = "Nom: $nom\nPrénom: $prenom\nVille: $ville\nCode Postal: $code_postal\nEmail: $email\nTéléphone: $telephone\n\nMessage:\n$message";
    $headers = "From: $email";

    if (mail($to, $subject, $body, $headers)) {
        echo "Message envoyé avec succès.";
    } else {
        echo "Échec de l'envoi du message.";
    }
}
?>
