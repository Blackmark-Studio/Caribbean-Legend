// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Todos los rumores de "+GetCityName(npchar.city)+" a su servicio. ¿Qué le gustaría saber?","Justo estábamos hablando de eso. Debes haberlo olvidado...","Esta es la tercera vez que me molestas ahora...","Estás repitiendo lo mismo como un loro...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabes, "+NPChar.name+", tal vez la próxima vez.","Bien, lo he olvidado por alguna razón...","Sí, realmente es la tercera vez...","Sí...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && !CheckAttribute(npchar, "quest.gonsales"))
			{
				link.l1 = "Estoy buscando a Enrique Gonzales. ¿Podrías decirme cómo encontrarlo?";
				link.l1.go = "saga";				
			}
		break;
			
		case "saga":
			dialog.text = "¡Todo el mundo conoce al Señor Gonzales! Su casa está junto a la autoridad portuaria.";
			link.l1 = "¿Cuántos años tiene?";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "Bueno, no lo sé con certeza, pero parece tener al menos cincuenta años. Ha estado viviendo en esa casa por bastante tiempo. Le gusta contar todo tipo de cuentos fantásticos sobre piratas que probablemente encontró solo en sus sueños.";
			link.l1 = "Parece que él es el hombre que necesito. Gracias, "+npchar.name+". Has sido de gran ayuda.";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			DialogExit();
			npchar.quest.gonsales = "true";
			pchar.questTemp.Saga.Gonsales = "true";
			pchar.quest.Saga_Gonsales1.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales1.win_condition.l1.location = "Cartahena_houseF2";
			pchar.quest.Saga_Gonsales1.function = "Saga_CreateGonsalesA";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
