// script.js
document.addEventListener("DOMContentLoaded", function() {
    const headerText = document.querySelector("header h1");
    headerText.style.transition = "text-shadow 0.5s ease-in-out";

    setInterval(() => {
        headerText.style.textShadow = 
            `0px 0px 10px #00e5ff, 
             0px 0px 20px #00e5ff, 
             0px 0px 30px #ff00cc`;
        
        setTimeout(() => {
            headerText.style.textShadow = "none";
        }, 500);
    }, 4000);

    const sections = document.querySelectorAll("section");
    const navLinks = document.querySelectorAll("nav a");

    window.addEventListener("scroll", () => {
        let currentSection = "";

        sections.forEach(section => {
            const sectionTop = section.offsetTop;
            const sectionHeight = section.clientHeight;
            if (scrollY >= sectionTop - sectionHeight / 3) {
                currentSection = section.getAttribute("id");
            }
        });

        navLinks.forEach(link => {
            link.classList.remove("active");
            if (link.getAttribute("href").includes(currentSection)) {
                link.classList.add("active");
            }
        });
    });
});
