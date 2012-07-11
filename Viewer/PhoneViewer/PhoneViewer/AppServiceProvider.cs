using System;
using System.Collections.Generic;

namespace PhoneViewer
{
    /// <summary>
    /// Implémente IServiceProvider pour l’application. Ce type est exposé par la propriété App.Services
    /// et peut être utilisé pour les ContentManagers ou autres types qui doivent accéder à IServiceProvider.
    /// </summary>
    public class AppServiceProvider : IServiceProvider
    {
        // Mappage du type de service aux services eux-mêmes
        private readonly Dictionary<Type, object> services = new Dictionary<Type, object>();

        /// <summary>
        /// Ajoute un nouveau service au fournisseur de services.
        /// </summary>
        /// <param name="serviceType">Type de service à ajouter.</param>
        /// <param name="service">L’objet de service proprement dit.</param>
        public void AddService(Type serviceType, object service)
        {
            // Valider l’entrée
            if (serviceType == null)
                throw new ArgumentNullException("serviceType");
            if (service == null)
                throw new ArgumentNullException("service");
            if (!serviceType.IsAssignableFrom(service.GetType()))
                throw new ArgumentException("service does not match the specified serviceType");

            // Ajouter le service au dictionnaire
            services.Add(serviceType, service);
        }

        /// <summary>
        /// Obtient un service du fournisseur de services.
        /// </summary>
        /// <param name="serviceType">Type de service à récupérer.</param>
        /// <returns>Objet de service enregistré pour le type spécifié..</returns>
        public object GetService(Type serviceType)
        {
            // Valider l’entrée
            if (serviceType == null)
                throw new ArgumentNullException("serviceType");

            // Récupérer le service du dictionnaire
            return services[serviceType];
        }

        /// <summary>
        /// Supprime un service du fournisseur de services.
        /// </summary>
        /// <param name="serviceType">Type de service à supprimer.</param>
        public void RemoveService(Type serviceType)
        {
            // Valider l’entrée
            if (serviceType == null)
                throw new ArgumentNullException("serviceType");

            // Supprimer le service du dictionnaire
            services.Remove(serviceType);
        }
    }
}
