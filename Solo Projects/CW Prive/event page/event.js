// Helper functions should be defined outside validateForm
function showError(elementId, message) {
    const errorElement = document.getElementById(elementId);
    errorElement.textContent = message;
    errorElement.style.display = 'block';
    const inputElement = errorElement.previousElementSibling;
    if (inputElement) {
        inputElement.classList.add('error');
    }
}

function hideError(elementId) {
    const errorElement = document.getElementById(elementId);
    errorElement.style.display = 'none';
    const inputElement = errorElement.previousElementSibling;
    if (inputElement) {
        inputElement.classList.remove('error');
    }
}

function validateForm(event) {
    event.preventDefault();
    let isValid = true;

    // Full Name validation
    const fullName = document.getElementById('fullName');
    if (fullName.value.length < 2) {
        showError('nameError', 'Name must be at least 2 characters long');
        isValid = false;
    } else {
        hideError('nameError');
    }

    // Date of Birth validation
    const dob = document.getElementById('dob');
    const parts = dob.value.split('/');
    if (parts.length !== 3) {
        showError('dobError', 'Please enter a valid date (dd/mm/yy)');
        isValid = false;
    } else {
        const today = new Date();
        const birthDate = new Date(2000 + parseInt(parts[2]), parts[1] - 1, parts[0]);
        const age = today.getFullYear() - birthDate.getFullYear();
        
        if (age < 18 || age > 30) {
            showError('dobError', 'Age must be between 18 and 30 years');
            isValid = false;
        } else {
            hideError('dobError');
        }
    }

    // Email validation
    const email = document.getElementById('email');
    if (!email.value.includes('@') || !email.value.includes('.')) {
        showError('emailError', 'Please enter a valid email address');
        isValid = false;
    } else {
        hideError('emailError');
    }

    // Gender validation
    const gender = document.getElementById('gender');
    if (!gender.value) {
        showError('genderError', 'Please select your gender');
        isValid = false;
    } else {
        hideError('genderError');
    }

    // Headshot validation
    const headshot = document.getElementById('headshot');
    if (headshot.files.length === 0) {
        showError('headshotError', 'Please upload a headshot photo');
        isValid = false;
    } else {
        const file = headshot.files[0];
        const fileSize = file.size / 1024 / 1024; 
        if (fileSize > 5) {
            showError('headshotError', 'File size must be less than 5MB');
            isValid = false;
        } else {
            hideError('headshotError');
        }
    }

    return isValid;
}

document.addEventListener('DOMContentLoaded', function() {
    flatpickr("#dob", {
        dateFormat: "d/m/y",
        maxDate: new Date().fp_incr(-6570), // 18 years ago
        minDate: new Date().fp_incr(-10950), // 30 years ago
        disableMobile: "true",
        allowInput: true,
        clickOpens: true,
        position: "below",
        theme: "dark",
    });

    document.querySelector('.calendar-icon').addEventListener('click', function() {
        document.getElementById('dob').focus();
    });
});