
void ApplyMigration(ref migrationState)
{
    ref rLoc = FindLocationById("SentJons_ExitTown");
    rLoc.fastreload = "SentJons";
    rLoc = FindLocationById("Bridgetown_ExitTown");
    rLoc.fastreload = "Bridgetown";
    rLoc = FindLocationById("Beliz_ExitTown");
    rLoc.fastreload = "Beliz";
    rLoc = FindLocationById("Caracas_ExitTown");
    rLoc.fastreload = "Caracas";
    rLoc = FindLocationById("Cartahena_ExitTown");
    rLoc.fastreload = "Cartahena";
    rLoc = FindLocationById("Cumana_ExitTown");
    rLoc.fastreload = "Cumana";
    rLoc = FindLocationById("BasTer_ExitTown");
    rLoc.fastreload = "BasTer";
    rLoc = FindLocationById("FortFrance_ExitTown");
    rLoc.fastreload = "FortFrance";
    rLoc = FindLocationById("Panama_ExitTown");
    rLoc.fastreload = "Panama";
    rLoc = FindLocationById("PortPax_ExitTown");
    rLoc.fastreload = "PortPax";
    rLoc = FindLocationById("SanAndres_ExitTown");
    rLoc.fastreload = "SanAndres";
    rLoc = FindLocationById("SanJuan_ExitTown");
    rLoc.fastreload = "SanJuan";
    rLoc = FindLocationById("SantaCatalina_ExitTown");
    rLoc.fastreload = "SantaCatalina";
    rLoc = FindLocationById("Santiago_ExitTown");
    rLoc.fastreload = "Santiago";
    rLoc = FindLocationById("SantoDomingo_ExitTown");
    rLoc.fastreload = "SantoDomingo";
    rLoc = FindLocationById("Marigo_ExitTown");
    rLoc.fastreload = "Marigo";
    rLoc = FindLocationById("Tortuga_ExitTown");
    rLoc.fastreload = "Tortuga";
    rLoc = FindLocationById("PortSpein_ExitTown");
    rLoc.fastreload = "PortSpein";
}
