void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iGun, iMush, qty;
	string sGroup, sLink, sText;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Carib" + locations[FindLocation(npchar.location)].index + "_";

	switch (Dialog.CurrentNode)
	{
	case "exit":
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		break;

	case "First time":
		dialog.text = "¡Felicidades! Esto es un error. Contacta a Jason y cuéntale cómo y dónde encontraste este. ¡Paz!";
		link.l1 = "¡Lo haré inmediatamente!";
		link.l1.go = "exit";
		Diag.TempNode = "First time";
		break;

	case "exit_fight":
		sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
		for (i = 0; i < iTemp; i++)
		{
			sld = CharacterFromID(sTemp + i);
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, sGroup);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, false);
		}
		LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(sGroup, "LandEnc_CaribAfrer");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "exit_peace":
		DialogExit();
		sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
		for (i = 0; i < iTemp; i++)
		{
			sld = CharacterFromID(sTemp + i);
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, sGroup);
			LAi_SetImmortal(sld, false);
			LAi_CharacterDisableDialog(sld);
		}
		ChangeIndianRelation(1.00);
		break;

	// военные индеи - карибы
	case "war_indian":
		for (i = 0; i < iTemp; i++)
		{
			sld = CharacterFromID(sTemp + i);
			LAi_type_actor_Reset(sld);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, false);
		}
		if (sti(pchar.questTemp.Indian.relation) > 79)
		{
			dialog.text = LinkRandPhrase("¡Salud a ti, hijo del mar! He oído hablar de ti. Puedes pisar tranquilo en nuestra tierra.", "" + npchar.name + " te saluda, hermano de cara pálida. Nos alegra verte como nuestro invitado.", "¡Te saludo, valiente guerrero de cara pálida!" + npchar.name + " se alegra de conocer a un amigo de los indios. ¡Vete en paz!");
			link.l1 = RandPhraseSimple("¡Y saludos a ti, hermano de piel roja! ¡Buena caza para ti!", "¡Saludos, valiente guerrero! ¡Que los dioses bendigan a ti y a tu familia!");
			link.l1.go = "exit_peace";
			if (CheckCaribGuns())
			{
				npchar.quest.count = 0;
				link.l2 = RandPhraseSimple("Tengo algo que podría ser interesante para ti, hermano de piel roja. ¿Quieres comerciar?", "Puedo ofrecerte comprar algo interesante, valiente guerrero. ¿Quieres comerciar?");
				link.l2.go = "war_indian_trade";
			}
		}
		else
		{
			dialog.text = LinkRandPhrase("¡Alto, cara pálida! ¿Con qué derecho caminas por mi tierra?", "¡Alto, hombre blanco! ¡Estás en la tierra de mis antepasados y mi tierra!", "¡Alto, cara pálida! No perteneces a mi tierra");
			link.l1 = RandPhraseSimple("¿Tu tierra? ¡Pierdete, escoria de cara roja!", "¡Mira a eso, un mono parlante! ¡Lárgate, ahora!");
			link.l1.go = "war_indian_1";
			link.l2 = RandPhraseSimple("He venido en paz, guerrero de piel roja. No deberíamos luchar por nada.", "No soy un enemigo para ti y tu tierra, guerrero. He venido en paz.");
			if (sti(pchar.questTemp.Indian.relation) + (makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) / 3)) > hrand(80))
				link.l2.go = "war_indian_2_1";
			else
				link.l2.go = "war_indian_2_2";
			link.l3 = RandPhraseSimple("He venido a comerciar contigo, no a luchar.", "No lucho con indios. Comercio con ellos.");
			if (sti(pchar.questTemp.Indian.relation) + (makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) / 6) + makeint(GetSummonSkillFromName(pchar, SKILL_FORTUNE) / 6)) > hrand(90))
				link.l3.go = "war_indian_3_1";
			else
				link.l3.go = "war_indian_3_2";
		}
		break;

	case "war_indian_1":
		dialog.text = RandPhraseSimple("¡Te arrepientes de haber nacido, perro de cara pálida... Arranco tu corazón y lo frío en el fuego!", "¡Te haré comer piedras, perro pálido! Nos reímos de ti suplicando por la muerte de rodillas, sabueso blanco!");
		link.l1 = RandPhraseSimple("¿Todavía no puedes cerrar tu apestosa boca, espantapájaros pintado? ¡Te llevaré de vuelta a la jungla de donde viniste!", "¿Te atreves a amenazarme, escoria?! ¡Bueno, ahora treparás de nuevo al árbol del que acabas de bajar!");
		link.l1.go = "exit_fight";
		break;

	case "war_indian_2_1":
		dialog.text = RandPhraseSimple("Oigo que tu voz habla con verdad. No desenfundamos nuestras hachas contra ti este día. Vete en paz, carapálida.", "El rostro pálido raramente trae paz, pero veo en tus ojos que hablas con verdad. Vete ahora.");
		link.l1 = RandPhraseSimple("Una decisión sabia, guerrero. Buena suerte a ti.", "Me alegra que llegáramos a un entendimiento, guerrero.");
		link.l1.go = "exit_peace";
		break;

	case "war_indian_2_2":
		dialog.text = RandPhraseSimple("¡Mientes, canalla pálido! ¡Viniste aquí para matar indios! ¿Listo para la batalla, rostro pálido?!", "Matas a los indios. La lengua blanca es lengua mentirosa. ¡La cortaré y la freiré en el fuego!");
		link.l1 = RandPhraseSimple("Bueno, compañero, no me culpes entonces. Dios sabe, traté de evitarlo...", "Bueno, lo pediste, guerrero.");
		link.l1.go = "exit_fight";
		break;

	case "war_indian_3_1":
		if (CheckCaribGuns())
		{
			npchar.quest.count = 0;
			dialog.text = "¿Comercio? Necesitamos arma de hombres blancos. ¡Un arma de fuego de rostro pálido! Por ella comerciamos nuestras mercancías. ¿Tienes arma de fuego para comerciar?";
			link.l1 = "Hmm. Sí. ¿Y qué me darás a cambio?";
			link.l1.go = "war_indian_trade";
			link.l2 = "¡Tú granuja! ¿Y luego dispararás a los colonos con mis pistolas? ¡No, eso no sucederá! En cuanto a vosotros, chacales, os cortaré a todos ahora...";
			link.l2.go = "exit_fight";
		}
		else
		{
			dialog.text = "¡Tú no tienes lo que queremos, rostro pálido... ¡Serás nuestro trofeo de guerra!";
			link.l1 = "Inténtalo si te atreves, espantapájaros...";
			link.l1.go = "exit_fight";
		}
		break;

	case "war_indian_3_2":
		dialog.text = RandPhraseSimple("¡No comerciamos con perros de cara pálida. ¡Matamos y tomamos!", "¡Nosotros no somos sucios miskito o arawaks, no comerciamos con caras pálidas! ¡Los matamos y obtenemos trofeos de guerra!");
		link.l1 = RandPhraseSimple("¡Bueno, entonces intenta robarme, malandrín!", "Primero, tendrás que quitarme mi sable, ¡tú basura!");
		link.l1.go = "exit_fight";
		break;

	case "war_indian_trade":
		iGun = 1;
		dialog.text = "Muestra lo que tienes, y diremos lo que damos a cambio.";
		for (i = 6; i >= 1; i--)
		{
			if (GetCharacterFreeItem(pchar, "pistol" + i) > 0)
			{
				sLink = "l" + iGun;
				link.(sLink) = "Offer " + XI_ConvertString("pistol" + i) + ".";
				link.(sLink).go = "gun_" + i;
				iGun++;
			}
		}
		break;

	case "gun_1":
		npchar.quest.gun = "pistol1";
		if (hrand(1) == 0)
		{
			npchar.quest.item = "potion" + (rand(2) + 2);
			iTotalTemp = hrand(1) + 1;
			sText = "" + FindRussianQtyString(iTotalTemp) + "  vial de poción curativa buena";
		}
		else
		{
			npchar.quest.item = "jewelry" + (hrand(9) + 14);
			iTotalTemp = hrand(2) + 1;
			sText = "" + FindRussianQtyString(iTotalTemp) + " esta hermosa piedra";
		}
		dialog.text = "¡Eh-ho! Te lo damos a cambio " + sText + ".";
		link.l1 = "¡Trato hecho!";
		link.l1.go = "war_indian_trade_agree";
		link.l2 = "No. De ninguna manera.";
		link.l2.go = "war_indian_trade_bad";
		break;

	case "gun_2":
		npchar.quest.gun = "pistol2";
		if (hrand(3) < 2)
		{
			npchar.quest.item = "potion" + (rand(2) + 2);
			iTotalTemp = hrand(2) + 2;
			sText = "" + FindRussianQtyString(iTotalTemp) + " vial de poción curativa buena";
		}
		else
		{
			npchar.quest.item = "jewelry" + (hrand(3) + 1);
			iTotalTemp = hrand(2) + 2;
			sText = "" + FindRussianQtyString(iTotalTemp) + " esta hermosa piedra";
		}
		dialog.text = "¡Eh-ho! Astuta arma... Te la damos a cambio " + sText + ".";
		link.l1 = "¡Trato hecho!";
		link.l1.go = "war_indian_trade_agree";
		link.l2 = "No. De ninguna manera.";
		link.l2.go = "war_indian_trade_bad";
		break;

	case "gun_3":
		npchar.quest.gun = "pistol3";
		if (hrand(5) < 3)
		{
			qty = rand(1) + 2;
			npchar.quest.item = "jewelry5" + qty;
			iTotalTemp = hrand(6) + qty * 15;
			sText = "" + FindRussianQtyString(iTotalTemp) + " esta hermosa perla";
		}
		else
		{
			npchar.quest.item = "jewelry" + (hrand(2) + 2);
			iTotalTemp = hrand(2) + 5;
			sText = "" + FindRussianQtyString(iTotalTemp) + "  esta hermosa piedra";
		}
		dialog.text = "¡Eh-ho! ¡Poderosa arma! ¡Matar muchos-muchos enemigos! Te lo damos a cambio " + sText + ".";
		link.l1 = "¡Trato hecho!";
		link.l1.go = "war_indian_trade_agree";
		link.l2 = "No. De ninguna manera.";
		link.l2.go = "war_indian_trade_bad";
		break;

	case "gun_4":
		npchar.quest.gun = "pistol4";
		if (hrand(9) < 8)
		{
			qty = rand(1) + 1;
			npchar.quest.item = "jewelry" + (qty + 4);
			iTotalTemp = hrand(10) + qty * 30;
			sText = "" + FindRussianQtyString(iTotalTemp) + " pedazo de metal que rostro pálido ama más que la vida";
		}
		else
		{
			npchar.quest.item = "obereg_" + (hrand(10) + 1);
			iTotalTemp = 1;
			sText = "este amuleto";
		}
		dialog.text = "¡Eh-ho! Temible arma... Te la damos a cambio " + sText + ".";
		link.l1 = "¡Trato hecho!";
		link.l1.go = "war_indian_trade_agree";
		link.l2 = "No. De ninguna manera.";
		link.l2.go = "war_indian_trade_bad";
		break;

	case "gun_5":
		npchar.quest.gun = "pistol5";
		if (hrand(7) < 7)
		{
			if (hrand(10) < 8)
			{
				npchar.quest.item = "jewelry7";
				iTotalTemp = 2 + hrand(1);
			}
			else
			{
				npchar.quest.item = "jewelry8";
				iTotalTemp = hrand(4) + 10;
			}
			qty = hrand(1) + 1;
			npchar.quest.item = "jewelry" + (qty + 6);
			if (qty == 1)
				iTotalTemp = 2;
			else
				iTotalTemp = hrand(5) + qty * 15;
			sText = "" + FindRussianQtyString(iTotalTemp) + " este hermoso y precioso alquitrán petrificado";
		}
		else
		{
			npchar.quest.item = "indian_" + (hrand(10) + 1);
			iTotalTemp = 1;
			sText = "este amuleto";
		}
		dialog.text = "¡Eh-oh! ¡Hermosa y poderosa arma! ¡Matar muchos-muchos enemigos! Te damos por ello " + sText + ".";
		link.l1 = "¡Trato hecho!";
		link.l1.go = "war_indian_trade_agree";
		link.l2 = "No. De ninguna manera.";
		link.l2.go = "war_indian_trade_bad";
		break;

	case "gun_6":
		npchar.quest.gun = "pistol6";
		if (hrand(9) < 8)
		{
			qty = rand(1) + 1;
			npchar.quest.item = "jewelry" + (qty + 4);
			iTotalTemp = hrand(8) + qty * 20;
			sText = "" + FindRussianQtyString(iTotalTemp) + " pedazo de metal que rostro pálido ama más que la vida";
		}
		else
		{
			npchar.quest.item = "amulet_" + (hrand(10) + 1);
			iTotalTemp = 1;
			sText = "este amuleto";
		}
		dialog.text = "¡Eh-ho! Arma útil... Te la damos a cambio " + sText + ".";
		link.l1 = "¡Trato hecho!";
		link.l1.go = "war_indian_trade_agree";
		link.l2 = "No. De ninguna manera.";
		link.l2.go = "war_indian_trade_bad";
		break;

	case "war_indian_trade_agree":
		ChangeIndianRelation(1.00);
		npchar.quest.count = sti(npchar.quest.count) + 1;
		TakeNItems(pchar, npchar.quest.item, iTotalTemp);
		RemoveItems(pchar, npchar.quest.gun, 1);
		Log_Info("Has entregado " + XI_ConvertString(npchar.quest.gun) + "");
		Log_Info("Has recibido " + XI_ConvertString(npchar.quest.item) + " por un importe de " + FindRussianQtyString(iTotalTemp) + "");
		PlaySound("interface\important_item.wav");
		if (sti(npchar.quest.count) > 3 + hrand(2))
			;
		{
			dialog.text = "Bien. Aquí tus bienes. No comerciamos más. Ven más tarde. Mejor arma ardiente más damos por ella. ¡Ahora vete!";
			link.l1 = "Adiós, guerrero de piel roja.";
			link.l1.go = "exit_peace";
		}
		else
		{
			dialog.text = "Bien. Aquí tienes tus bienes. ¿Tienes más armas de fuego para intercambiar?";
			if (CheckCaribGuns())
			{
				link.l1 = "Lo tengo. ¿Comprarás?";
				link.l1.go = "war_indian_trade";
			}
			link.l2 = "No. La próxima vez traeré más.";
			link.l2.go = "war_indian_trade_exit";
		}
		break;

	case "war_indian_trade_exit":
		dialog.text = "Trae. Mejor arma de fuego, más damos por ella. ¡Ahora vete!";
		link.l1 = "Hasta la vista, guerrero...";
		link.l1.go = "exit_peace";
		break;

	case "war_indian_trade_bad":
		if (sti(pchar.questTemp.Indian.relation) > 79)
		{
			DialogExit();
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_SetImmortal(sld, false);
				LAi_CharacterDisableDialog(sld);
			}
		}
		else
		{
			dialog.text = "¡Entonces nos llevamos todo gratis, cara pálida!";
			link.l1 = "Puedes intentarlo...";
			link.l1.go = "exit_fight";
		}
		break;

	// мирные индеи - мискито
	case "peace_indian":
		for (i = 0; i < iTemp; i++)
		{
			sld = CharacterFromID(sTemp + i);
			LAi_type_actor_Reset(sld);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, false);
		}
		dialog.text = LinkRandPhrase("Saludos, hombre blanco. ¿Qué necesitas en nuestra selva?", "Nuestra selva es muy peligrosa. ¿Qué haces aquí?", "¿Qué te trae por aquí, valiente cara pálida?");
		link.l1 = RandPhraseSimple("Solo estaba pasando, mi amigo de piel roja. Creo que hay suficiente espacio en este camino para ambos, ¿no?", "¡Saludos, hijo de la selva! Estoy aquí por negocios, y no lucho contra los indios.");
		link.l1.go = "peace_indian_1";
		link.l2 = RandPhraseSimple("¿Y por qué necesitas saberlo? Ve por tu propio camino y mantente alejado de los problemas!", "Vete por tu camino, piel roja. No tengo tiempo para hablar contigo.");
		link.l2.go = "peace_indian_2";
		break;

	case "peace_indian_1":
		dialog.text = RandPhraseSimple("Somos gente pacífica. No somos enemigos de los hombres blancos. Ve, pero ten cuidado en nuestra tierra!", "Me alegra encontrarme con el amigo pálido de los indios. Ve en paz, hijo del mar!");
		link.l1 = RandPhraseSimple("Buena suerte a ti también, hijo de la selva...", "Adiós, amigo de piel roja.");
		link.l1.go = "exit_peace";
		break;

	case "peace_indian_2":
		dialog.text = RandPhraseSimple("Somos cazadores pacíficos. ¡Pero no nos quedamos quietos cuando cara pálida habla así en nuestra tierra!", "No luchamos con hombres blancos, pero si los hombres blancos nos ofenden, respondemos como nuestros antepasados nos enseñaron!");
		link.l1 = RandPhraseSimple("¿Todavía no puedes cerrar tu maloliente boca, espantapájaros pintado? ¡Te enviaré de vuelta a la jungla de donde viniste!", "¿Te atreves a amenazarme, escoria?! ¡Ahora subirás de nuevo al árbol del que acabas de bajar!");
		link.l1.go = "exit_fight";
		break;
	}
}
