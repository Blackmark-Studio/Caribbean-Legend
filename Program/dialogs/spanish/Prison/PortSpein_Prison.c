// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Habla, te escucho";
			link.l1 = "Me equivoqué. Adiós.";
			link.l1.go = "Exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "Me informaron que tienes una epidemia aquí, ¿es correcto?";
				link.l1.go = "Consumption";
			}
		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "Eres correcto, así que evita visitar las mazmorras sin una razón seria. ¿Por qué te interesa esto?";
			link.l1 = "Solo por curiosidad. Entonces, si mis muchachos se emborrachan demasiado, hacen mucho ruido y terminan aquí, ¿debo preparar un poco de lino amarillo entonces?";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "Lamentablemente, señor, no entiendo la broma en caso de que estuvieras bromeando. Las mazmorras están húmedas y frías y conoces el clima. La tisis es una visita frecuente en estas mazmorras. Incluso tengo que pagar a mis muchachos por llevar comida a las cámaras. Patrullar allí se considera lo mismo que el trabajo forzado.";
			link.l1 = "Lamento, solo quería saber, ¿cuán serio es esto?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "Demasiado serio. Ni siquiera tenemos un médico aquí, él también murió de esa maldita tisis. Ahora solo un médico de la guarnición examina a los prisioneros una vez a la semana. Pero ¿a quién le importan estos vagabundos y criminales?\nLa mayoría de la gente piensa que se merecen totalmente ese destino y es difícil discutir sobre esto.";
			link.l1 = "Mis conocimientos de medicina son modestos, pero por lo que sé, la tisis es peligrosa y mortal, pero no mata a las personas en pocos días como aquí. ¿No deberían las víctimas sufrir durante meses o incluso años?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "Como acabas de mencionar, no eres médico, por lo tanto hablar sobre las características de la enfermedad podría ser simplemente... una mentira inventada. Solo repetí lo que nuestro médico había estado diciendo antes de que la enfermedad se lo llevara también. Así que no entiendo tu curiosidad y comportamiento cínico. ¡La gente muere aquí!";
			link.l1 = "¿No acabas de decir que se lo merecían?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "¡Basta, señor! Creo que tú y yo tenemos otros asuntos que atender en lugar de competir en ingenio. La puerta está justo detrás de ti.";
			link.l1 = "Está bien, perdona mi falta de tacto, ya me voy.";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			DialogExit();
			npchar.quest.Consumption = "true";
			pchar.questTemp.Consumption.Commandant = "true";
			AddQuestRecord("Consumption", "3");
			pchar.quest.Consumption.win_condition.l1 = "location";
			pchar.quest.Consumption.win_condition.l1.location = "PortSpein_houseF2";
			pchar.quest.Consumption.function = "Consumption_CommandantHouse";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
