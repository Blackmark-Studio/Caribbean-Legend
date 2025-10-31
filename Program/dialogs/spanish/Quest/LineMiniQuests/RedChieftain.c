void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "Esto es un error. Avisad a los desarrolladores.";
		link.l1 = "¡Lo haré!";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "RedChieftain":
		dialog.text = "¿Cómo, cara pálida? Veo que eres el capitán de la gran canoa. Yo Kanauri. Soy el jefe de Caimán - poderosa tribu Arawak. Yo quiero hablar contigo.";
		link.l1 = "Te escucho, jefe. ¿Qué problemas te han traído a mí?";
		link.l1.go = "RedChieftain_0";
		link.l2 = "¿Qué quieres de mí, simio de piel roja y maloliente? Vuelve a tus junglas y no me molestes con tus peticiones.";
		link.l2.go = "RedChieftain_exit";
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
		break;

	case "RedChieftain_exit":
		dialog.text = "¡Gu-u! ¿No enseñaron al capitán blanco a ser educado? Me hicieron una oferta. Ganas un montón de wampum pero ahora me voy. Adiós, cara pálida.";
		link.l1 = "Vete, piérdete...";
		link.l1.go = "RedChieftain_exit_1";
		break;

	case "RedChieftain_exit_1":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
		npchar.lifeday = 0;
		DeleteAttribute(pchar, "questTemp.RedChieftain");
		chrDisableReloadToLocation = false;
		ChangeIndianRelation(-3.0);
		break;

	case "RedChieftain_0":
		dialog.text = "Hermano blanco perspicaz como búho, astuto como serpiente. Problema ocurriendo a indio. Gran-gran canoa de hombres blancos llega a mi aldea. Se llevan a muchos Cayman, mi gente, los ponen en su canoa y los sacan hacia la Madre de Todas las Aguas...";
		link.l1 = "Espera... ¿estás diciendo que tu gente fue esclavizada por hombres blancos de un barco?";
		if (sti(pchar.Basenation) == SPAIN)
			link.l1.go = "RedChieftain_2";
		else
			link.l1.go = "RedChieftain_1";
		break;

	case "RedChieftain_1":
		dialog.text = "Hermano blanco, hablas con verdad. Sé que esos rostros pálidos no son amigos tuyos. Esos crueles hombres blancos de la tribu española. Ellos toman a mi gente. Pero yo los encuentro. Los españoles hacen trabajar al indio de alba a anochecer, sumergirse en la Madre de las Aguas, encontrar conchas llenas de lágrimas de los dioses.";
		link.l1 = "Buceo de perlas... Ese es un trabajo brutal.";
		link.l1.go = "RedChieftain_3";
		pchar.questTemp.RedChieftain.Spa = "true";
		pchar.questTemp.RedChieftain.AttackNation = SPAIN;
		break;

	case "RedChieftain_2":
		dialog.text = "Habláis con verdad, hermano blanco. Sé que esa gente no son amigos tuyos. Ellos de la tribu inglesa. Ellos toman a mi gente. Pero yo los encuentro. Los ingleses hacen que el indio trabaje de amanecer a anochecer, se sumerja en la Madre de las Aguas, encuentre conchas llenas de lágrimas de los dioses.";
		link.l1 = "Buceo de perlas... Este es un trabajo duro.";
		link.l1.go = "RedChieftain_3";
		pchar.questTemp.RedChieftain.Eng = "true";
		pchar.questTemp.RedChieftain.AttackNation = ENGLAND;
		break;

	case "RedChieftain_3":
		dialog.text = "Indio enfermo y muere por esclavitud. Hombre blanco no tiene piedad por indio. Látigo y pistola son la ley del blanco para el indio. Yo viejo. No tengo hombres para luchar. Caimanes Arawaks gente pacífica, inventamos pipa de la paz. Te pido, hermano blanco, que desenvaines látigo y pistola contra el malvado blanco, salva al indio Arawak.";
		link.l1 = "¿Me estás pidiendo que declare la guerra? Debes entender, jefe, que mis recursos son limitados.";
		link.l1.go = "RedChieftain_4";
		break;

	case "RedChieftain_4":
		dialog.text = "No vayas en camino de guerra. Libera al indio. Mi gente. Te damos todas las lágrimas de los dioses que tenemos en las canoas. Mata al malvado blanco, ayuda al indio, obtén lágrimas de los dioses, véndelas por mucho-mucho wampum. Montón de wampum.";
		link.l1 = "Ah, ya veo. No, Canauri, no puedo ayudarte. No puedo hacerlo ahora - mi barco necesita reparaciones, no quedan suministros...";
		link.l1.go = "RedChieftain_wait";
		link.l2 = "En ese caso, será un placer. Hablemos de los detalles. ¿Dónde está tu gente? Dijiste que ya los habías encontrado...";
		link.l2.go = "RedChieftain_5";
		break;

	case "RedChieftain_wait":
		dialog.text = "¡Gu-u! Puedo esperar, hermano blanco... Estaré en este puerto una luna más, buscando al protector de mi gente. Encuéntrame aquí cuando estés listo.";
		link.l1 = "...";
		link.l1.go = "RedChieftain_wait_1";
		break;

	case "RedChieftain_wait_1":
		DialogExit();
		// LAi_ActorGoToLocator(npchar, "quest", "quest1", "RedChieftainStay", -1);
		chrDisableReloadToLocation = false;
		bDisableFastReload = false;
		SetFunctionTimerCondition("RedChieftainDelete", 0, 0, 30, false);

		sld = CharacterFromID("RedChieftain");
		// LAi_SetStayType(sld);
		sld.dialog.currentnode = "RedChieftain_wait_2";
		AddLandQuestMark(sld, "questmarkmain");
		AddMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity, false);
		break;

	case "RedChieftain_wait_2":
		dialog.text = "¿Has vuelto, hermano blanco? ¿Me ayudarás a castigar a los hombres malvados y salvar al indio?";
		link.l1 = "Más listo no voy a estar.";
		link.l1.go = "RedChieftain_wait_4";
		link.l2 = "Todavía necesito prepararme.";
		link.l2.go = "RedChieftain_wait_3";
		break;

	case "RedChieftain_wait_3":
		dialog.text = "Estaré aquí, hermano blanco.";
		link.l1 = "... ";
		link.l1.go = "exit";
		NextDiag.Tempnode = "RedChieftain_wait_2";
		break;

	case "RedChieftain_wait_4":
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
		dialog.text = "¡Estoy muy contento de que hayas aceptado, hermano blanco!";
		link.l1 = "Hablemos de los detalles, Canauri. ¿Dónde están tus hombres? Dijiste que ya los habías encontrado...";
		link.l1.go = "RedChieftain_5";
		pchar.quest.RedChieftainDelete.over = "yes"; // снять таймер
		break;

	case "RedChieftain_5":
		if (CheckAttribute(pchar, "questTemp.RedChieftain.Spa"))
		{
			AddMapQuestMarkShore("Shore19", true);
			pchar.questTemp.RedChieftain.Island = "Cumana";
			pchar.questTemp.RedChieftain.Shore = "Shore19";
			pchar.questTemp.RedChieftain.Add1 = "Spanish";
			pchar.questTemp.RedChieftain.Add2 = "Cala Carupano, no lejos de Cumaná";
			dialog.text = "Están acampados en Carupano Cove, cerca del campamento español llamado Cumana. Cada día navegan en botes por el mar, se sumergen en el agua, muy-muy profundo...";
			link.l1 = "Ya veo. ¿Y los españoles los vigilan mientras bucean?";
			link.l1.go = "RedChieftain_6";
		}
		else
		{
			AddMapQuestMarkShore("Shore54", true);
			pchar.questTemp.RedChieftain.Island = "SantaCatalina";
			pchar.questTemp.RedChieftain.Shore = "Shore54";
			pchar.questTemp.RedChieftain.Add1 = "English";
			pchar.questTemp.RedChieftain.Add2 = "Cabo Perlas, no lejos de Blueweld";
			dialog.text = "Hacen campamento en el Cabo Perlas cerca del campamento inglés llamado Blueweld. Cada día navegan en botes por el mar, se sumergen en el agua, bien profundo...";
			link.l1 = "Ya veo. Y, por supuesto, ¿los ingleses los vigilan?";
			link.l1.go = "RedChieftain_6";
		}
		break;

	case "RedChieftain_6":
		dialog.text = "Sí, dos grandes canoas de rostros pálidos con palos de fuego y grandes cuchillos. Campamento en la orilla también vigilado - indio no puede escapar.";
		link.l1 = "¿Qué tipo de barcos? ¿Puedes describirlos? ¿Qué tan grandes son? ¿Qué tipo de velas?";
		link.l1.go = "RedChieftain_7";
		break;

	case "RedChieftain_7":
		dialog.text = "Esta canoa es grande, pero Canauri ha visto más grandes. La vela de proa está muy, muy inclinada, hace tres lados así. (Dibuja tres velas latinas y una vela trapezoidal en la tierra) La parte superior es estrecha, la inferior es ancha.";
		link.l1 = "Parece un goleta...";
		link.l1.go = "RedChieftain_8";
		break;

	case "RedChieftain_8":
		dialog.text = "Canauri no conoce esa palabra. Rostro pálido tener mucho cuidado si ven otra canoa - desembarcarán indio y esperarán hasta que la otra canoa se aleje.";
		link.l1 = "Precavidos hijos de perra...¿cómo puedo acercarme a ellos?";
		link.l1.go = "RedChieftain_9";
		break;

	case "RedChieftain_9":
		dialog.text = "Si el hermano rostro pálido toma una canoa pequeña, entonces puede acercarse sigilosamente a la orilla. Yo mostraré el camino. Pero trae solo una canoa pequeña o el perro rostro pálido verá y ahuyentará al indio del bote hacia las selvas...";
		link.l1 = "Entendido. Necesitaré un lugre o un balandro para esta operación. Genial. Un balandro contra dos goletas... Dios... y yo que pensaba que esto iba a ser fácil.";
		link.l1.go = "RedChieftain_10";
		break;

	case "RedChieftain_10":
		dialog.text = "¿Nos vamos, hermano blanco? Tenemos menos de una luna.";
		link.l1 = "Sí. Súbete a mi barco, jefe. ¡No perdamos tiempo!";
		link.l1.go = "RedChieftain_11";
		break;

	case "RedChieftain_11":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
		AddPassenger(pchar, npchar, false);
		SetCharacterRemovable(npchar, false);
		chrDisableReloadToLocation = false;
		bDisableFastReload = false;
		pchar.quest.Red_Chieftain_2.win_condition.l1 = "location";
		pchar.quest.Red_Chieftain_2.win_condition.l1.location = pchar.questTemp.RedChieftain.Island;
		pchar.quest.Red_Chieftain_2.function = "RedChieftain_CreateShooner";
		if (bImCasual)
			NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		SetFunctionTimerCondition("RedChieftainOver", 0, 0, 30, false);
		AddQuestRecord("RedChieftain", "1");
		AddQuestUserData("RedChieftain", "sText1", pchar.questTemp.RedChieftain.Add1);
		AddQuestUserData("RedChieftain", "sText2", pchar.questTemp.RedChieftain.Add2);
		break;

	case "RedChieftain_pearl":
		dialog.text = "¡Gracias, hermano blanco! ¡Salvaste a la tribu Arawak de Caimán! Te debemos una gran deuda. El camino está libre del perro cara pálida y el indio puede correr libre en las selvas. Te damos todas las lágrimas de dioses dejadas en los barcos.";
		link.l1 = "Bueno, veamos qué tienes...";
		link.l1.go = "RedChieftain_pearl_1";
		break;

	case "RedChieftain_pearl_1":
		DialogExit();
		pchar.questTemp.RedChieftain.Ind = 1;
		AddDialogExitQuest("RedChieftain_Pearl");
		break;

	case "RedChieftain_pearl_give":
		int iSmallPearl = rand(200) + rand(250) + rand(200) + 250;
		int iBigPearl = rand(100) + rand(100) + rand(50) + 150;
		TakeNItems(pchar, "jewelry52", iBigPearl);
		TakeNItems(pchar, "jewelry53", iSmallPearl);
		PlaySound("interface\important_item.wav");
		Log_SetStringToLog("El Jefe te ha dado " + iSmallPearl + " pequeñas y " + iBigPearl + " perlas grandes.");
		dialog.text = LinkRandPhrase("¡Me alegra que las lágrimas de los dioses sean tuyas, hermano de Arawak!", "¡Indio agradecido, valiente rostro pálido!", "¡Toma nuestra captura, hermano blanco!");
		link.l1 = LinkRandPhrase("¡Encantado de ayudarte!", "¡Gracias, hermano piel roja!", "¡Estupendo!");
		link.l1.go = "exit";
		pchar.questTemp.RedChieftain.Ind = sti(pchar.questTemp.RedChieftain.Ind) + 1;
		AddDialogExitQuest("RedChieftain_Pearl");
		break;

	case "RedChieftain_final":
		chrDisableReloadToLocation = false; // открыть локацию
		// belamour legendary edition -->
		if (sti(pchar.questTemp.RedChieftain.Tartane) > 5)
		{
			dialog.text = "Canauri te agradece de nuevo, ¡hermano cara pálida! ¡Rescatas todas las canoas con el indio! Para Canauri es muy importante salvar todas las canoas porque también salvaste al nieto de Canauri, a quien el malvado cara pálida llevó a la esclavitud. De niño, a mi nieto le encantaba nadar mucho, y Canauri le dio este amuleto encantado para que el nieto no se ahogue. Ahora el nieto ya no quiere nadar y me da el amuleto para que yo pueda dártelo a ti, hermano de cara pálida. Espero que las lágrimas de los dioses y este regalo sean una recompensa suficiente por la vida de Arawak. Y ahora nos despedimos, es hora de que regresemos a nuestra aldea natal.";
			link.l1 = "¡Buena suerte, Cunauri! ¡Me alegra que tu nieto haya sobrevivido! ¡Rezo para que este mal nunca vuelva a caer sobre ti!";
			link.l1.go = "RedChieftain_final_1Obereg";
		}
		else
		{
			dialog.text = "¡Canauri te agradece de nuevo, hermano cara pálida! Espero que las lágrimas de los dioses sean suficiente recompensa por la vida de los indios. Ahora adiós, vamos a la aldea nativa.";
			link.l1 = "¡Buena suerte, Cunauri! ¡Nunca vuelvas a caer en la esclavitud!";
			link.l1.go = "RedChieftain_final_1";
		}
		if (SandBoxMode)
		{
			// if(CheckAttribute(pchar,"questTemp.SanBoxTarget"))
			//{
			// if(makeint(pchar.questTemp.SanBoxTarget) == 2 ||  makeint(pchar.questTemp.SanBoxTarget) == 5)
			//{
			pchar.questTemp.SanBoxTarget.RedChieftain = true;
			ChangeCharacterComplexReputation(pchar, "fame", 25);
			//}
			//}
		}
		break;

	case "RedChieftain_final_1Obereg":
		DialogExit();
		RemovePassenger(Pchar, npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
		npchar.lifeday = 0;
		int n1 = pchar.questTemp.RedChieftain.Tartane;
		for (i = 1; i <= n1; i++)
		{
			sld = characterFromId("RC_Indian_" + i);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
		}
		InterfaceStates.Buttons.Save.enable = true; // разрешить сохраняться
		TakeNItems(pchar, "talisman10", 1);
		PlaySound("interface\important_item.wav");
		Log_Info("Has recibido el buscador de Obereg");
		locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; // энкаутеры открыть
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddCharacterExpToSkill(pchar, "Fortune", 50); // везение
		AddQuestRecord("RedChieftain", "9");
		CloseQuestHeader("RedChieftain");
		DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		// <-- legendary edition

	case "RedChieftain_final_1":
		DialogExit();
		RemovePassenger(Pchar, npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
		npchar.lifeday = 0;
		int n = pchar.questTemp.RedChieftain.Tartane;
		for (i = 1; i <= n; i++)
		{
			sld = characterFromId("RC_Indian_" + i);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
		}
		InterfaceStates.Buttons.Save.enable = true;											   // разрешить сохраняться
		locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; // энкаутеры открыть
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddCharacterExpToSkill(pchar, "Fortune", 50); // везение
		AddQuestRecord("RedChieftain", "8");
		CloseQuestHeader("RedChieftain");
		DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
