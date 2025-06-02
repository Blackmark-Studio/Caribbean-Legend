// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Todos los rumores de "+GetCityName(npchar.city)+" a su servicio. ¿Qué le gustaría saber?","Justo estábamos hablando de eso. Debes haberlo olvidado...","Esta es la tercera vez hoy que hablas de alguna pregunta...","Repites lo mismo como un loro...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabes, "+NPChar.name+", tal vez la próxima vez.","  Cierto, lo he olvidado por alguna razón...  ","Sí, realmente es la tercera vez...","Sí...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatTortuga") // работорговец
            {
                link.l1 = "Escucha, ¿dónde puedo encontrar a Francois Gontier? Se suponía que ya había llegado a Tortuga.";
                link.l1.go = "Tortuga_ratT_1";
            }
			// суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "Busco a Henri Thibaut. ¿Dónde puedo encontrarlo?";
				link.l1.go = "terrapin";
			}
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga1" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "Busco a Henri Thibaut. ¿Dónde puedo encontrarlo?";
				link.l1.go = "terrapin_2";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga")
			{
				link.l1 = "Dime, ¿un barco llamado 'Santa Margarita' ha parado en tu colonia últimamente? ¿Quizás como un premio corsario?";
                link.l1.go = "guardoftruth";
			}
			// Addon 2016-1 Jason Пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Jeweller"))
			{
				link.l1 = "Escucha, amigo, estoy buscando a Gaspard Parmentier. ¿Dónde puedo encontrarlo?";
                link.l1.go = "mtraxx_jew";
			}
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(npchar, "quest.PZ.Ask.Block"))
			{
				link.l1 = "¿Puedes ayudarme un poco, camarada? Estoy buscando a un hombre llamado Joep Van Der Vink. ¿Lo conoces?";
				link.l1.go = "PZ1";
			}
        break;
        
		case "Tortuga_ratT_1":
			dialog.text = "¿Francois Gontier? ¿Quién es él? No conozco a ningún hombre con ese nombre.";
			link.l1 = "Es capitán de la corbeta '"+pchar.questTemp.Slavetrader.ShipName+"''.";
			link.l1.go = "Tortuga_ratT_2";
        break;
		
		case "Tortuga_ratT_2":
			dialog.text = "No tengo la menor idea, camarada. Y ningún barco con ese nombre ha atracado en nuestro puerto, de eso estoy seguro.";
			link.l1 = "Está bien, ¿has visto a algún forastero últimamente en el pueblo?";
			link.l1.go = "Tortuga_ratT_3";
        break;
		
		case "Tortuga_ratT_3":
			dialog.text = "¡Buena pregunta! Esto es una ciudad portuaria, no una aldea. Los forasteros pasan por aquí todos los días. Aunque he oído sobre cinco tipos extraños, siempre se mantienen juntos y tienen sus espadas listas.\nLa patrulla incluso preguntó por ellos sin resultado. Pero estoy seguro de que no llegaron aquí en ningún barco como el que mencionas, no se ha visto ninguna nave así por aquí, ¿entiendes?";
			link.l1 = "Mm... Está bien, ya veo. Gracias, "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_8");
			pchar.questTemp.Slavetrader = "wait1";//затычка
        break;
		
		// суп из черепахи
		case "terrapin":
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Monsieur Thibaut es un hombre famoso en Tortuga. Su mansión está ubicada cerca de la autoridad portuaria. Al salir de la taberna, dirígete directamente hacia el puerto. Acércate al arco que conduce al puerto, gira a la izquierda en la encrucijada y baja hasta el final de la calle, donde te encontrarás con un edificio de piedra de dos pisos con un techo rojo. Esa es la mansión de Monsieur Thibaut.";
			link.l1 = "¡Gracias! Iré a visitarlo...";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			DialogExit();
			pchar.questTemp.Terrapin = "house";
			sld = characterFromId("Tibo");
			ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "barmen", "stay");
			LAi_SetOwnerType(sld);
		break;
		
		case "terrapin_2":
			dialog.text = "Monsieur Thibaut está muy solicitado hoy, un mensajero del gobernador acaba de venir corriendo aquí. También estaba interesado. ¿Es tan difícil encontrarlo? Lleva alquilando una habitación en el segundo piso desde hace bastante tiempo, aunque tiene toda una mansión para vivir. No sé para qué la necesita, pero entra mucho más a menudo de lo que sale. Y solo está allí por las tardes.";
			link.l1 = "Tal vez, él está aquí ahora mismo.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			if (stf(environment.time) < 20.0 && stf(environment.time) > 8.0)
			{
				dialog.text = "No. Él dijo que no volvería hasta las ocho de la tarde de hoy. Puedes intentar buscarlo en su mansión, pero no creo que lo encuentres allí. Lo vi navegando en un lugre de patrulla.";
				link.l1 = "¡Gracias! Pasaré a verlo más tarde.";
				link.l1.go = "terrapin_4";
			}
			else
			{
				dialog.text = "Sí. Si quieres, puedes subir.";
				link.l1 = "¡Gracias! Iré a visitarlo...";
				link.l1.go = "terrapin_4";
			}
		break;
		
		case "terrapin_4":
			DialogExit();
			pchar.questTemp.Terrapin = "tavern";
			sld = characterFromId("Tibo");
			sld.dialog.currentnode = "tibo_9";
			LAi_SetLoginTime(sld, 20.0, 8.0);
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "goto", "goto1");
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false); // откроем комнату
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], true);//запретить драться
			LAi_SetStayType(sld);
			// Addon 2016-1 Jason Пиратская линейка
			if (GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			if (GetCharacterIndex("Helena") != -1)
			{
				sld = characterFromId("Helena");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
		break;
		
		case "guardoftruth":
			dialog.text = "No tengo ni idea del nombre del barco, era 'Santa Margarita' o 'Cortesana Castellana'... Pero trajeron aquí un galeón español capturado. ¡Capturado por un balandro, nada menos! ¡Eso sí que es auténtica jodida navegación! Gaius Marchais, su capitán, ha estado alardeando durante dos días en la taberna, ¡su primer viaje y tal premio!\nSí, una hazaña muy heroica, abordar un galeón lleno de ratas de iglesia sin soldados para protegerlos. Parece que esos malditos papistas olvidaron lo que dicen sobre aquellos que se ayudan a sí mismos...";
			link.l1 = "Sí, Dios ayuda a quien se ayuda a sí mismo, eso es un dicho hugonote seguro. ¿Cómo puedo echar un vistazo a ese capitán afortunado? ¿Está aquí, en Tortuga?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ah, ¿quién diablos lo sabe? No lo he visto en mi taberna desde hace mucho tiempo. Tan pronto como se puso sobrio, compró un barco nuevo y reluciente con el dinero del premio y corría por su cubierta como un loco. No tengo idea de dónde está Marchais ahora. Tal vez esté en Tortuga, o tal vez en el mar.";
			link.l1 = "Está bien. ¡Gracias por la historia, camarada!";
			link.l1.go = "guardoftruth_2";			
		break;
		
		case "guardoftruth_2":
			dialog.text = "En cualquier momento, monsieur. Siempre estoy feliz de ayudar a nuestro querido Capitán "+pchar.name+", ¡salvador de Saint-Pierre! ¡Pasa más tarde!";
			link.l1 = "...";
			link.l1.go = "exit";	
			AddQuestRecord("Guardoftruth", "8");
			pchar.questTemp.Guardoftruth = "tortuga1";
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_jew":
            dialog.text = "Parece que Gaspard se está volviendo cada vez más popular entre los tuyos. Su casa está junto a la muralla. Gira a la izquierda desde la taberna y dirígete al puerto, pero no vayas allí, gira a la izquierda otra vez, sigue recto y luego gira a la derecha. Una casa de dos pisos.";
			link.l1 = "¡Gracias!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekJewellerHouse");
		break;
		
		case "PZ1":
			dialog.text = "Nunca he oído hablar de él.  ";
			link.l1 = "Tal vez use otro nombre. ¿Quizás lo hayas oído como el capitán del bergantín 'Banten'?";
			link.l1.go = "PZ2";
		break;
		
		case "PZ2":
			dialog.text = "Jamás he oído hablar de ese bergantín tampoco.";
			link.l1 = "He oído que estuvo aquí recientemente. ¿Quizás un poco de plata refresque tu memoria?";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			npchar.quest.PZ.Ask.Block = true;
			
			dialog.text = "Bueno, pregunta dónde lo oíste. Aunque no me importa tomar tu plata.";
			link.l1 = "Entonces, no hay plata esta vez. Hasta luego.";
			link.l1.go = "Exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
