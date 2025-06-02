void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "exit":
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		break;

	case "Exit_Fight":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		LAi_SetPlayerType(pchar);
		for (i = 1; i <= 3; i++)
		{
			if (GetCharacterIndex("GangMan_" + i) == -1)
				continue;
			sld = CharacterFromID("GangMan_" + i);
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "OpenTheDoors");

		if (pchar.GenQuest.EncGirl == "RapersTreasure")
		{
			LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
		}
		else
		{
			LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
		}
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "exit_noFight":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		for (i = 1; i <= 3; i++)
		{
			if (GetCharacterIndex("GangMan_" + i) == -1)
				continue;
			sld = CharacterFromID("GangMan_" + i);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
			LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld) - 1, false, "LandEnc_RapersBeforeDialog");
		}
		sld = CharacterFromID("CangGirl");
		LAi_SetActorType(sld);
		LAi_ActorAfraid(sld, npchar, true);
		DialogExit();
		AddDialogExitQuest("OpenTheDoors");
		break;

	case "First time":
		for (i = 1; i <= 3; i++)
		{
			if (GetCharacterIndex("GangMan_" + i) == -1)
				continue;
			sld = CharacterFromID("GangMan_" + i);
			LAi_type_actor_Reset(sld);
			LAi_RemoveCheckMinHP(sld);
		}
		//			Diag.TempNode = "OnceAgain";
		if (pchar.GenQuest.EncGirl == "Begin_1")
		{
			dialog.text = LinkRandPhrase("Ve a tu propio camino, " + GetSexPhrase("compañero", "chica") + ". Ella nos agradecerá al final, ya sabes.", "¡Lárgate! Deja que los caballeros se diviertan un poco.", "Esto no es asunto tuyo, " + GetSexPhrase("extraño", "muchacha") + ". ¡Solo nos divertiremos, y eso es todo!");
			link.l1 = LinkRandPhrase("¡No permitiré esto!", "¡Abandona tus malvados planes al instante!", "¡No toleraré ninguna violencia!");
			link.l1.go = "Node_Fight";
			link.l2 = RandPhraseSimple("Lo tengo, me voy. Lo siento por molestar.", "No me atreveré a molestarte más. Siento haberte molestado.");
			link.l2.go = "Exit_NoFight";
			pchar.GenQuest.EncGirl = "Begin_11";
		}
		if (pchar.GenQuest.EncGirl == "Begin_2")
		{
			if (sti(pchar.rank) < 10)
			{
				dialog.text = LinkRandPhrase("Ve a tu propio camino, " + GetSexPhrase("compañero", "chica") + ". Ella nos agradecerá al final, ya sabes.", "¡Piérdete! Deja que los caballeros se diviertan un rato.", "Esto no es asunto tuyo, " + GetSexPhrase("extraño", "muchacha") + ". ¡Solo nos divertiremos un poco, y eso es todo!!");
				link.l1 = LinkRandPhrase("¡No lo permitiré!", "¡Abandona tus malvados planes al instante!", "¡No toleraré ninguna violencia!");
				link.l1.go = "Node_Fight";
				link.l2 = RandPhraseSimple("Lo tengo, me voy. Lo siento por molestar.", "No me atreveré a molestarte más. Lo siento por haberte molestado.");
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_11";
			}
			else
			{
				dialog.text = RandPhraseSimple("Oye, " + GetSexPhrase("extraño", "señorita") + ", ¿por qué buscas problemas? Esta chica es una 'conocida', individual, en nuestro asentamiento. Ya la hemos pagado, pero te vio y decidió huir con nuestro dinero.", "Oye, " + GetSexPhrase("compañero", "chica") + ", sigue tu propio camino y no te entrometas en nuestros asuntos. Ganamos a esta chica en un juego de dados, pero fue un poco rápida así que huyó, la hemos estado persiguiendo durante una hora en esta selva.");
				link.l1 = "¡No me importa, no te dejaré hacerle daño!";
				link.l1.go = "Node_3";
				link.l2 = RandPhraseSimple("¡Oh, ya veo! ¡Y casi le creí! ¡Qué bruja...", "Ah, bueno, eso es otro asunto entonces. ¡Diviértanse, muchachos!");
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_22";
			}
		}
		if (pchar.GenQuest.EncGirl == "Begin_3")
		{
			if (sti(pchar.rank) < 20)
			{
				dialog.text = "Ve a tu propio camino, " + GetSexPhrase("buen hombre", "Joven señorita") + ". Lo resolveremos sin ti.";
				link.l1 = "¡No toleraré ninguna violencia!";
				link.l1.go = "Node_5";
				pchar.GenQuest.EncGirl = "Begin_33";
			}
			else
			{
				dialog.text = RandPhraseSimple("Oye, " + GetSexPhrase("extraño", "señorita") + ", ¿por qué buscas problemas? Esta chica es una 'conocida', individual, en nuestro asentamiento. Ya le hemos pagado, pero te vio y decidió huir con nuestro dinero.", "Oye, " + GetSexPhrase("compañero", "muchacha") + ", sigue tu propio camino y no te metas en nuestros asuntos. Ganamos a esta chica en un juego de dados, pero fue un poco rápida para huir, la hemos estado persiguiendo durante una hora.");
				link.l1 = "¡No me importa, no te permitiré hacerle daño!";
				link.l1.go = "Node_3";
				link.l2 = RandPhraseSimple("¡Ah, ya veo! ¡Y casi le creí a la muy fulana...!", "Ah, bueno, eso es otra cosa entonces. Bueno, diviértanse chicos!");
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_22";
			}
		}
		break;

	case "Node_Fight":
		dialog.text = RandPhraseSimple("" + GetSexPhrase("Bueno, ciertamente has elegido el momento adecuado para un paseo...", "Entonces, ¿decidiste ser un héroe?") + " ¡Encargaros de " + GetSexPhrase("él", "ella") + ", muchachos!", "Tú, " + GetSexPhrase("baboso", "escoria") + ", ¡¿Te atreves a interponerte en nuestro camino?! ¡Máten" + GetSexPhrase("lo", "la") + "!");
		link.l1 = "¡He visto a gente más amenazante!";
		link.l1.go = "Exit_Fight";
		break;

	case "Node_3":
		pchar.GenQuest.EncGirl.price = 1100 * (rand(4) + 5) + 200 * sti(pchar.rank);
		dialog.text = "¡Deberías saber que ella nos costó bastante! Y si eres tan noble, puedes tomarla por " + sti(pchar.GenQuest.EncGirl.price) + " pesos." + GetSexPhrase("Te lo pasarás bien con ella, je-je...", "") + "";
		if (sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.price))
		{
			link.l1 = RandPhraseSimple("Aquí está tu dinero. Me la llevo conmigo.", "Deja de rechinar los dientes. Me llevo a la chica conmigo. Aquí está tu dinero.");
			link.l1.go = "Node_4";
		}
		link.l2 = LinkRandPhrase("¿Así que lo que quieres es dinero? ¿Qué tal acero frío?", "¿Se supone que eso es gracioso?, ¡mira a la chica, tonto! ¡Está asustada!", "¿A quién intentas engañar, degenerado?");
		link.l2.go = "Node_Fight";
		break;

	case "Node_4": // бандюки уходят, девица остаётся - ГГ ее выкупил у бандюков
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.price)));
		ChangeCharacterComplexReputation(pchar, "nobility", 7);
		// pchar.quest.LandEnc_RapersBadExit.over = "yes";
		sGlobalTemp = "Saved_CangGirl";
		pchar.GenQuest.EncGirl.Ransom = true;
		sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
		for (i = 1; i <= 3; i++)
		{
			if (GetCharacterIndex("GangMan_" + i) == -1)
				continue;
			sld = CharacterFromID("GangMan_" + i);
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			if (i == 1)
				LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
			else
				LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", 5.0);
		}
		DialogExit();
		AddDialogExitQuestFunction("EncGirl_Saved");
		break;

	case "Node_5":
		dialog.text = "¿Por qué la crees en primer lugar? ¿Qué violencia? Huyó de casa, y nuestro jefe nos ha enviado para encontrarla.";
		link.l1 = RandPhraseSimple("Bueno, eso es otra historia, entonces. Ve, persigue a tu fugitivo.", "Oh, ya veo. Bueno, sigue persiguiéndola entonces... y tengo algunos asuntos que atender.");
		link.l1.go = "Exit_NoFight";
		link.l2 = RandPhraseSimple("¡Cuenta estos cuentos de hadas a tus nietos, si vives lo suficiente para tenerlos!", "¿A quién intentas engañar, cabrón?!");
		link.l2.go = "Node_6";
		link.l3 = "La llevaré a casa por mí mismo, para evitar algo malo. ¿Quiénes son sus padres?";
		link.l3.go = "Node_7";
		break;

	case "Node_6":
		dialog.text = "¿Quieres morir? Esa es tu elección...";
		link.l1 = "Mira quién habla.";
		link.l1.go = "Exit_Fight";
		break;

	case "Node_7":
		sGlobalTemp = "Saved_CangGirl";
		if (pchar.GenQuest.EncGirl.city == "Panama")
			i = hrand(2);
		else
			i = hrand(3);
		switch (i)
		{
		case 0:
			pchar.GenQuest.EncGirl.FatherNom = "es propietario de una tienda";
			pchar.GenQuest.EncGirl.FatherGen = "del dueño de una tienda";
			pchar.GenQuest.EncGirl.Father = "store_keeper";
			break;
		case 1:
			pchar.GenQuest.EncGirl.FatherNom = "sirve en la oficina portuaria";
			pchar.GenQuest.EncGirl.FatherGen = "que trabaja en la oficina portuaria";
			pchar.GenQuest.EncGirl.Father = "portman_keeper";
			break;
		case 2:
			pchar.GenQuest.EncGirl.FatherNom = "es el comandante de la prisión";
			pchar.GenQuest.EncGirl.FatherGen = "del comandante de una prisión";
			pchar.GenQuest.EncGirl.Father = "fort_keeper";
			break;
		case 3:
			pchar.GenQuest.EncGirl.FatherNom = "es propietario de un astillero";
			pchar.GenQuest.EncGirl.FatherGen = "del propietario de un astillero";
			pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
			break;
		}
		dialog.text = "Su padre " + pchar.GenQuest.EncGirl.FatherNom + ", en el asentamiento de " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ". Pero por favor, no nos falles, porque él no es alguien con quien jugar, nos despellejará a todos vivos...";
		link.l1 = "No te preocupes. La entregaré a él.";
		link.l1.go = "Node_12";
		pchar.GenQuest.EncGirl = "toParents";
		break;

	case "Node_12":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		pchar.quest.LandEnc_RapersBadExit.over = "yes";
		ChangeCharacterComplexReputation(pchar, "nobility", 5);
		sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
		for (i = 1; i <= 3; i++)
		{
			if (GetCharacterIndex("GangMan_" + i) == -1)
				continue;
			sld = CharacterFromID("GangMan_" + i);
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, true);
			if (i == 1)
				LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
			else
				LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", 5.0);
			sld.lifeDay = 0;
		}
		DialogExit();
		AddDialogExitQuestFunction("EncGirl_Saved");
		break;

	case "Node_8":
		dialog.text = "Y así nos encontramos de nuevo. ¿Dónde está tu compañera? Oh, bueno, en realidad no la necesito, si tú estás aquí.";
		link.l1 = "Caballeros, realmente creo que ya habéis recibido suficiente dinero como para dejar a la chica en paz.";
		link.l1.go = "Node_9";
		break;

	case "Node_9":
		if (hrand(1) == 0)
		{
			pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;
		}
		else
		{
			pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);
			pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;
		}
		pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
		switch (hrand(4))
		{
		case 0:
			sTemp = "una pierna";
			break;
		case 1:
			sTemp = "un brazo";
			break;
		case 2:
			sTemp = "una oreja";
			break;
		case 3:
			sTemp = "una nariz";
			break;
		case 4:
			sTemp = "un ojo";
			break;
		}
		dialog.text = "¿Qué es tu dinero comparado con los tesoros de " + GetName(pchar.GenQuest.EncGirl.PirateIdx, pchar.GenQuest.EncGirl.PirateName1, NAME_GEN) + "? " + "Él era tan avaro que no quería casar a su propia hija porque quería evitar gastos extra...\nPero tiene nuestra parte en sus cofres! " + GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.PirateName2, NAME_NOM) + " ha perdido en el abordaje " + sTemp + "¡¿Y qué tienes en su lugar?!" + "¿Patética pizca de plata?" + GetName(pchar.GenQuest.EncGirl.PirateIdx, pchar.GenQuest.EncGirl.PirateName1, NAME_NOM) + "siempre se llevaba todo el botín a su escondite. ¡Pero ahora no vamos a rendirnos! ¡Muéstranos dónde están sus cofres!";
		link.l1 = "Bueno, ciertamente no me postulé para custodiar los tesoros de vuestro capitán, pero no puedo mostrarte el lugar... Porque no sé dónde está ese lugar.";
		link.l1.go = "Node_10";
		break;

	case "Node_10":
		dialog.text = "¡Estás mintiendo!!! ¡Puedo oler el aroma del oro que sale de esta cueva! ¡Muéstrame el lugar si no quieres morir!";
		link.l1 = "Veo que mis palabras no lograron convencerte. ¿Quizás, mi espada será más expresiva?";
		link.l1.go = "Node_11";
		break;

	case "Node_11":
		pchar.GenQuest.EncGirl = "RapersTreasure";
		dialog.text = "Tú " + GetSexPhrase("canalla", "porquería") + "¡Apártate de mi camino!";
		link.l1 = "¡Argh!";
		link.l1.go = "exit_fight";
		break;

	case "EncGirl_Berglar":
		dialog.text = "Hola, bueno " + GetSexPhrase("hombre", "señora") + ". Tenemos quejas sobre ti.";
		link.l1 = "¿Quejas de quién? ¿De esa puta?";
		link.l1.go = "EncGirl_Berglar1";
		break;

	case "EncGirl_Berglar1":
		dialog.text = "Cuida tu lengua, ¿vale? ¡No permitiré que insultes a mi hermana! Primero la acosaste en la selva, luego la trajiste aquí " + GetSexPhrase("para más indecencia", "y me robó") + ".";
		link.l1 = "Oye compañero, ¿realmente tengo que escuchar todo eso?";
		link.l1.go = "EncGirl_Berglar2";
		break;

	case "EncGirl_Berglar2":
		pchar.GenQuest.EncGirl.BerglarSum = makeint(sti(pchar.money) / 5) + 5000;
		if (sti(pchar.GenQuest.EncGirl.BerglarSum) > 250000)
			pchar.GenQuest.EncGirl.BerglarSum = 220000 + rand(30000);
		if (sti(pchar.GenQuest.EncGirl.BerglarSum) > 0)
		{
			dialog.text = "No. Una suma modesta de solo " + sti(pchar.GenQuest.EncGirl.BerglarSum) + " pesos te salvarán de todos los problemas.";
			if (sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.BerglarSum))
			{
				link.l1 = "Bueno, las nobles acciones ciertamente son un poco costosas estos días. Está bien, tómalo...";
				link.l1.go = "EncGirl_Berglar3";
			}
			link.l2 = "Creo que sería más barato hacer un agujero en tu vientre para que no te interpongas en mi camino a la salida.";
			link.l2.go = "EncGirl_Berglar4";
		}
		else
		{
			dialog.text = "No. Pero también vaciarás tus bolsillos, de lo contrario te apuñalaré!";
			link.l1 = "¡Está bien, tómalo, granuja! Pero no te saldrás con la tuya...";
			link.l1.go = "EncGirl_Berglar3_1";
			link.l2 = "Creo que sería más fácil hacer un agujero en tu vientre para que no te interpongas en mi camino a la salida.";
			link.l2.go = "EncGirl_Berglar4";
		}
		break;

	case "EncGirl_Berglar3":
		AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.BerglarSum)));
		dialog.text = "Muy bien. Buen viaje.";
		link.l1 = "Buena suerte.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("EncGirlFack_outRoom");
		break;

	case "EncGirl_Berglar3_1":
		dialog.text = "Por supuesto que no, por supuesto... Bueno, Adiós a ti, " + GetSexPhrase("compañero", "chica") + "." + GetSexPhrase(" Y ten en cuenta, no eres tan guapo que cualquier chica se habría enamorado de ti en el instante que te vio. Esa sería mi lección para ti.", "") + "";
		link.l1 = "" + GetSexPhrase("¡Eso es seguro!..", "¡Pierde ya!") + "";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("EncGirlFack_outRoomRaped");
		break;

	case "EncGirl_Berglar4":
		dialog.text = "Pareces " + GetSexPhrase("un hombre tan noble", "una dama tan bien educada") + ", ¿por qué el mal lenguaje?";
		link.l1 = "Me conviene más...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("EncGirlFack_fight");
		break;

	case "Node_2":
		dialog.text = "¡Bueno, tú lo pediste! ¿Deberíamos hacerle cosquillas " + GetSexPhrase("", "") + "con nuestro acero, muchachos?";
		Link.l1 = "¡Reza antes de morir!";
		Link.l1.go = "Exit_Fight";
		break;

	case "OnceAgain":
		Diag.TempNode = "OnceAgain";
		dialog.text = "¿Qué?, ¿te gustaría unirte? " + GetSexPhrase("¡Piérdete, no hay suficiente para todos nosotros", "¡Fuera de aquí, una moza es suficiente para nosotros") + "!";
		Link.l1 = "Bueno, entonces no te molestaré.";
		Link.l1.go = "Exit_NoFight";
		Link.l2 = "¡No permitiré que ocurra ninguna violencia!";
		Link.l2.go = "Node_2";
		break;
	}
}
