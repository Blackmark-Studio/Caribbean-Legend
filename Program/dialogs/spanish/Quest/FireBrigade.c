
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
    string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
// ГРИФФОНДОР -->
		case "FireBrigade_fra":
			dialog.text = GetSexPhrase("", "Una mujer... ¡y capitana! Ahora sí lo he visto todo. Mademoiselle, es usted encantadora. Lástima que su belleza haya traído tanta desgracia a la Corona de Francia\n") + "Así terminan todas las órdenes de Poincy. Uno en prisión. El otro—o se le une, o cae hoy en combate.";
			link.l1 = "Está claro que este no es tu lugar. ¿Por qué enviar a un oficial tan brillante y a un barco tan hermoso a hacer el trabajo sucio de un cazador de recompensas?";
			link.l1.go = "FraOff_1";
		break;

        case "FraOff_1":
			dialog.text = "Las órdenes no se discuten, se cumplen. Si cada capitán eligiera qué órdenes merecen la pena—no tendríamos armada.";
			link.l1 = "Díselo a tus hombres.";
			link.l1.go = "FraOff_2";
        break;

        case "FraOff_2":
			dialog.text = "Me has acorralado y tratas de quebrar mi lealtad y mi juramento. Eso es bajo, dadas las circunstancias. Terminemos esto con el choque de espadas, no con palabras.";
			link.l1 = "(Liderazgo) Hay una tercera opción. Deja de hacer el trabajo sucio que no es digno de un oficial. Únete a mí—te mostraré otro mundo.";
			link.l1.go = "FraOff_HireCheck";
            link.l2 = "¡Entonces, a las armas!";
			link.l2.go = "FraOff_ExitFight";
        break;

        case "FraOff_HireCheck":
            if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 80)
            {
                notification("¡Habilidad insuficientemente desarrollada! (80)", SKILL_LEADERSHIP);
                dialog.text = "A los traidores se les trata igual en todas partes. Y yo no seré uno.";
                link.l1 = "Tuviste tu oportunidad, y la perdiste. ¡En guardia!";
                link.l1.go = "FraOff_ExitFight";
                break;
            }
            notification("¡Comprobación superada!", SKILL_LEADERSHIP);
            dialog.text = "Juré lealtad a la corona, no a burócratas pomposos que nos mandan a morir para tapar sus propios líos. Pero tú eres enemigo de mi rey, y no puedo ignorarlo.";
			link.l1 = "Podría redimir mis pecados contra tu país mañana mismo—solo hay que pagar al intermediario adecuado. Eso dice más de tus superiores que de mí.";
			link.l1.go = "FraOff_Sucess";
        break;

        case "FraOff_Sucess":
			dialog.text = "Es cierto. Y ya estoy cansado de soportarlo. Estoy listo para servir bajo tu mando, si prometes dejar en paz a los franceses.";
			link.l1 = "No sé con quién nos cruzaremos, y no puedo prometer nada. Pero prometo ser razonable. Bienvenido a la tripulación, oficial " + NPChar.name + "!"; // своего имени он вообще-то не называл
			link.l1.go = "FraOff_Hired";
        break;

        case "FraOff_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();	
        break;

        case "FraOff_Hired":
            AddBrigadierOfficer(sld, NPChar);
            DialogExit();
        break;

// ЭЛЬ КАСАДОР -->
		case "FireBrigade_spa":
            // to_do: чек нуля?
			dialog.text = "Así que este es el enemigo público. Espero que estés orgulloso de ese título, pirata. Te lo has ganado a pulso\nSegún la Casa de Contratación, has hundido " + (Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0)) + " barcos bajo la bandera de la Corona española. Y hoy, mi hermoso barco se sumará a esa lista" + GetSexPhrase(".","\n¡Ay de la flota española! Hemos sufrido enfermedades, favoritismos, traiciones... ¿Pero ser derrotados por una mujer?");
			link.l1 = "Eres el último en pie, tu tripulación está muerta. Y tú también, solo que aún no lo sabes.";
			link.l1.go = "Alonso_1";
			if(Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0) < 1)
			{
				Achievment_Set("ach_CL_159")
			}
		break;

		case "Alonso_1":
			dialog.text = "Es una pena que de Alba no recibiera esta misión. Lo habría hecho mejor. Pero intentaré terminar el trabajo.";
			link.l1 = "Eres un verdadero hijo de tu patria. Prepárate para encontrarte con sus héroes, señor.";
			link.l1.go = "Alonso_2";
			link.l2 = "El cazador se ha convertido en presa. Todos tus discursos no sirvieron de nada—tan viejo como el mundo.";
			link.l2.go = "Alonso_3";
		break;

		case "Alonso_2":
            ChangeCharacterComplexReputation(PChar, "nobility", 5);
			dialog.text = "Gracias por este respiro, pero ahora hablará mi espada.";
			link.l1 = "¡A las armas!";
			link.l1.go = "Alonso_ExitFight";
		break;

        case "Alonso_3":
            ChangeCharacterComplexReputation(PChar, "nobility", -5);
			dialog.text = "Gracias por este respiro, pero ahora hablará mi espada.";
			link.l1 = "¡Prepárate para morir!";
			link.l1.go = "Alonso_ExitFight";
		break;

        case "Alonso_ExitFight":
        	SetCharacterPerk(NPChar, "Rush");
            ActivateCharacterPerk(NPChar, "Rush");
            PlaySound("Ambient\Tavern\glotok_001.wav");
            PlaySound("Types\" + LanguageGetLanguage() + "\warrior03.wav");
            SendMessage(NPChar, "lfffsfff", MSG_CHARACTER_VIEWSTRPOS, 0.0, 0.0, 0.1, XI_ConvertString("Rampage"), 255.0, 30.0, 30.0);
            NPChar.Unpushable = "";
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

// ХИМЕРА -->
        case "FireBrigade_eng":
            // to_do: ты-вы у элен
            dialog.text = GetSexPhrase(PChar.Name + "! Tu nombre aparece tanto en los informes que siento que ya nos conocemos de toda la vida", "¡Señorita McArthur! ¿Sabe su patrón lo que está haciendo? Bah, da igual. Seguro que él será mi próximo encargo") + "\nTienes suerte: a mis jefes les encantan las órdenes urgentes que contradicen las anteriores. Si no estuviera ocupado limpiando el equipo viejo de Antigua... Bueno, basta. Me estás distrayendo de mi verdadero trabajo.";
			link.l1 = "Tú también me distraes.";
			link.l1.go = "Cortny_ExitFight";
		break;

        case "Cortny_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("KnippelAppearance");
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();	
		break;

        case "Kneepel":
            dialog.text = "¡Bola encadenada a popa, casi se me escapa! Si mis viejos huesos fueran un poco más rápidos, habría mandado a ese bastardo al diablo yo mismo. Gracias, capitán. Y también gracias de parte de mi difunto patrón.";
			link.l1 = "¿Quién eres? ¿Un prisionero? ¿Mi tripulación te liberó?";
			link.l1.go = "Kneepel_1";	
		break;

        case "Kneepel_1":
            dialog.text = "Charlie Knippel en persona. ¡El mejor artillero de la marina inglesa!";
			link.l1 = "Courtney dijo que tardó mucho en encontrarte. ¿Qué pasó?";
			link.l1.go = "Kneepel_2";	
		break;

        case "Kneepel_2":
            dialog.text = "Durante muchos años serví a un valiente capitán inglés llamado Richard Fleetwood. Luchamos muchas batallas juntos, por verdadera pasión a la marina inglesa. Pero un día, todo cambió\nLos jefes de Londres nos usaron como peones. Atacamos a los nuestros. Ensuciamos nuestros uniformes limpiando los errores de otros. Y ahora nos toca a nosotros...";
			link.l1 = "No te juzgo. La vida es complicada, sobre todo si no eres dueño de tu destino.";
			link.l1.go = "Kneepel_2_good";
            link.l2 = "¿Dirías que las sombras de viejos pecados por fin te alcanzaron?";
			link.l2.go = "Kneepel_2_bad";
		break;

        case "Kneepel_2_good":
            dialog.text = "No me arrepiento de haber servido a mi país. Solo... duele, capitán. Sobre todo por mi patrón y su pobre esposa.";
			link.l1 = "¿Y ahora qué?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_2_bad":
            TEV.NoKneepel = "";
            dialog.text = "No hace falta que me pinches... Ya hemos pagado de sobra por nuestros pecados.";
			link.l1 = "¿Y ahora qué?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_3":
            dialog.text = "Ahora soy un hombre sin nombre ni patria. Podría ir a cualquier parte, pero por ahora no hay a dónde ir. Y nadie con quién ir. Se necesitan artilleros en todas partes, pero no todos los barcos tienen cañones.";
			link.l1 = "Únete a mí. No puedo decir que tenga la mejor relación con la marina inglesa, pero respeto a los mejores.";
            if(!CheckAttribute(&TEV, "NoKneepel"))
                link.l1.go = "Kneepel_3_good";
            else
                link.l1.go = "Kneepel_3_bad";
            link.l2 = "Tengo cañones. Si eres tan bueno, siempre habrá sitio para un profesional de verdad en mi tripulación.";
			link.l2.go = "Kneepel_3_bad";
		break;

        case "Kneepel_3_good":
            dialog.text = "En casa me espera la horca, igual que con los españoles y los holandeses, y los franceses no me caen bien. Pero parece que necesitas un buen artillero. Estoy dentro, capitán. Iré a la cabina en cuanto pueda. Pásate algún día, brindamos con bolas encadenadas.";
			link.l1 = "Bienvenido a bordo.";
			link.l1.go = "Kneepel_Hired";	
		break;

        case "Kneepel_3_bad":
            dialog.text = "No, gracias. Prefiero requisar un bote y perderme en el rincón más profundo del archipiélago. Gracias por salvarme, capitán, y adiós.";
			link.l1 = "...";
			link.l1.go = "Kneepel_Escape";	
		break;

        case "Kneepel_Escape":
            DeleteAttribute(&TEV, "NoKneepel");
            DeleteAttribute(&TEV, "boardingReloadFreeze");
            NPChar.lifeday = 0;
            LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1.0);
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;

        case "Kneepel_Hired":
            DeleteAttribute(&TEV, "NoKneepel");
            DeleteAttribute(&TEV, "boardingReloadFreeze");
            NPChar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
            NPChar.Dialog.CurrentNode = "Knippel_officer";
            NPChar.quest.OfficerPrice = sti(PChar.rank)*200; // Артефакт
            npchar.quest.meeting = true;
            NPChar.OfficerImmortal = true;
            NPChar.Health.HP    = 60.0;
            NPChar.Health.maxHP = 60.0;
            NPChar.OfficerWantToGo.DontGo = true;
            NPChar.loyality = MAX_LOYALITY;
            NPChar.Payment = true;
            NPChar.DontClearDead = true; 
            SaveCurrentNpcQuestDateParam(NPChar, "HiredDate");
            AddPassenger(pchar, NPChar, false);
            SetCharacterRemovable(NPChar, true);
            LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1.0);
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;

// МЕЙФЕНГ -->
        case "FireBrigade_hol":
			dialog.text = "No eres quien debía llegar hasta aquí. Meifeng es el colmillo de la Compañía. Mi escuadrón es la hoja que castiga. Los rompiste. Solo. Eso... no pasa a menudo.";
			link.l1 = "Te enviaron tras de mí como si fuera una bestia. Y luché—como un animal acorralado. Cuando es luchar o morir, la mente se aclara. Al final, solo queda una pregunta: ¿Llegaré a la cabina de la legendaria xebec—o no?";
			link.l1.go = "Longway_1";
		break;

		case "Longway_1":
			dialog.text = GetSexPhrase("", "Extraño—ver a una mujer en una pelea así. En el Imperio Celeste, las mujeres no mandan flotas. Pero tú no eres menos. Quizá hasta das más miedo\n") + "¿Sabías quién mandaba? ¿Me esperabas?";
			link.l1 = "Sí. Meifeng es un barco con historia. Cuando me crucé con los holandeses, supe que tarde o temprano te mandarían tras de mí. Habría sido un final honorable... pero mira cómo ha salido todo.";
			link.l1.go = "Longway_2";
		break;

		case "Longway_2":
			dialog.text = "Conocer al enemigo y a uno mismo es la clave de la victoria. Así que tomaste tu decisión. Enfrentaste a mi escuadrón en tus propios términos. Estabas listo para morir. Pero ganaste. Ahora mi vida está en tus manos. ¿Por qué no terminas el trabajo?";
			link.l1 = "(Liderazgo) Porque no veo sentido en hundir a un capitán legendario solo por las ambiciones de la Compañía. Yo también fui un peón. Serví intereses ajenos, obedecí órdenes ajenas. Te ofrezco lo que yo mismo elegí una vez: libertad.";
            if (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP) >= 50)
                link.l1.go = "Longway_Success";
            else
                link.l1.go = "Longway_Failed";
            link.l2 = "Porque todo capitán merece la última palabra. ¡En guardia!";
			link.l2.go = "Longway_ExitFight";
		break;

		case "Longway_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

		case "Longway_Failed":
            notification("¡Habilidad insuficientemente desarrollada! (50)", SKILL_LEADERSHIP);
			dialog.text = "La libertad no es algo que se da. Es algo que se toma. Y no todos los que hablan de elección pueden ofrecerla. Hay caminos que no se pueden evitar. Hay órdenes que no se pueden dejar sin cumplir. Mi camino está aquí. Mi orden es resistir hasta el final.";
			link.l1 = "¿Entonces eliges la muerte?";
			link.l1.go = "Longway_Failed_over";
		break;

		case "Longway_Failed_over":
			dialog.text = "No. Elijo seguir siendo yo mismo.";
			link.l1 = "¡En guardia!";
			link.l1.go = "Longway_ExitFight";
		break;

		case "Longway_Success":
            notification("¡Comprobación superada!", SKILL_LEADERSHIP);
			dialog.text = "No eres como Rodenburg. Él me veía como una herramienta. Tú—como un igual. Sacrificarse no es una virtud. Estoy listo para escuchar tus condiciones.";
			link.l1 = "Es sencillo. Sé mi navegante en mi buque insignia. O, si lo prefieres, tendrás tu propio barco y navegarás bajo mi bandera. Ya no tendrás que limpiar los trapos sucios de la Compañía ni esconder sus esqueletos en el armario. Soy libre—y te ofrezco compartir esa libertad conmigo.";
			link.l1.go = "Longway_Success_over";
		break;

		case "Longway_Success_over":
			dialog.text = "He visto mucho: sangre, oro, traición. La Compañía paga—pero no respeta. Te da un barco—pero te mantiene encadenado. Tú... das una opción. Si cumples tu palabra—Longwei ya no será un cazador a las órdenes de otros. Será un hombre. Un capitán. O—al lado de un capitán que sabe a dónde va.";
			link.l1 = "Bienvenido a la tripulación, navegante Longwei.";
			link.l1.go = "Longway_Hired";
		break;

		case "Longway_Hired":
            sld = GetCharacter(NPC_GenerateCharacter("Longway_FP", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
			sld.name = StringFromKey("QuestsUtilite_42");
			sld.lastname = StringFromKey("QuestsUtilite_43");
			sld.greeting = "Longway";
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.currentnode = "Longway_officer";
			sld.rank = 20;
			sld.money = 5000;
			SetSelfSkill(sld, 45, 45, 45, 40, 50);
			SetShipSkill(sld, 50, 20, 25, 25, 65, 20, 20, 50, 15);
			SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
			LAi_SetHP(sld, 250, 250);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "SailingProfessional");
            sTemp = GetGeneratedItem("blade_41");
            GiveItem2Character(sld, sTemp);
            EquipCharacterbyItem(sld, sTemp);
            sTemp = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
            if(sTemp != "")
            {
                GiveItem2Character(sld,   sTemp);
                EquipCharacterbyItem(sld, sTemp);
                sTemp = LAi_GetCharacterBulletType(NPChar, GUN_ITEM_TYPE);
                LAi_SetCharacterBulletType(sld, sTemp);
                LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, sTemp);
                sTemp = LAi_GetCharacterGunpowderType(NPChar, GUN_ITEM_TYPE);
                if(sTemp != "") AddItems(sld, sTemp, 30 + rand(20));
            }
			TakeNItems(sld, "potion2", 1);
            sld.quest.meeting = true;
			sld.quest.OfficerPrice = sti(pchar.rank)*200; // Артефакт
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.OfficerImmortal = true;
			sld.Health.HP    = 60.0;
			sld.Health.maxHP = 60.0;
            sld.CanTakeMushket = true;
			SetCharacterPerk(sld, "ShipEscape");
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

            NPChar.lifeday = 0;
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
            LAi_SetActorType(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);

            AddDialogExitQuest("pchar_back_to_player");
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;
	}
}

// TO_DO
void AddBrigadierOfficer(ref sld, ref NPChar)
{
    string sTemp = NationShortName(NPChar.nation);
    sld = GetCharacter(NPC_GenerateCharacter("FraBrigadier", NPChar.model, "man", NPChar.model.animation, 30, FRANCE, -1, false, "quest"));
    float num = 1.0;
    switch (MOD_SKILL_ENEMY_RATE)
	{
		case  1: num = 0.5;  break;
		case  2: num = 0.6;  break;
		case  3: num = 0.7;  break;
		case  4: num = 0.8;  break;
		case  5: num = 0.9;  break;
		case  6: num = 1.0;  break;
		case  7: num = 1.1;  break;
		case  8: num = 1.2;  break;
		case  9: num = 1.3;  break;
		case 10: num = 1.5;  break;
	}
    num = stf(NPChar.Rank) / num;
    FantomMakeCoolFighter(sld, MakeInt(num+2), 70, 70, BLADE_LONG, "", "", 100);
    RemoveAllCharacterItems(sld, true);
    GiveItem2Character(sld, NPChar.equip.blade);
    EquipCharacterbyItem(sld, NPChar.equip.blade);
    sTemp = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
    if(sTemp != "")
    {
        GiveItem2Character(sld,   sTemp);
        EquipCharacterbyItem(sld, sTemp);
        sTemp = LAi_GetCharacterBulletType(NPChar, GUN_ITEM_TYPE);
        LAi_SetCharacterBulletType(sld, sTemp);
        LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, sTemp);
        sTemp = LAi_GetCharacterGunpowderType(NPChar, GUN_ITEM_TYPE);
        if(sTemp != "") AddItems(sld, sTemp, 30 + rand(20));
    }
    sld.name = NPChar.name;
    sld.lastname = NPChar.lastname;
    sld.greeting = "officer_hire";
    sld.Dialog.Filename = "Enc_Officer_dialog.c";
    sld.quest.meeting = true;
    sld.quest.OfficerPrice = sti(PChar.rank)*200; // Артефакт
    Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
    sld.OfficerImmortal = true;
    sld.Health.HP    = 60.0;
    sld.Health.maxHP = 60.0;
    sld.OfficerWantToGo.DontGo = true;
    sld.loyality = MAX_LOYALITY;
    AddDialogExitQuest("pchar_back_to_player");
    AddDialogExitQuestFunction("LandEnc_OfficerHired");
    NPChar.lifeday = 0;
    LAi_SetActorType(NPChar);
    LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
    PostEvent("LAi_event_boarding_EnableReload", 5000);
}
