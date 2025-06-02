// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Habla, te estoy escuchando";
			link.l1 = "Me equivoqué. Adiós.";
			link.l1.go = "Exit";
		break;
		
		case "tonzag_bail":
			NextDiag.TempNode = "First_officer";
		
			dialog.text = "¿Cuál es el propósito de vuestra visita a Tortuga, Capitán?";
			link.l1 = "¡Te lo ruego! ¡Ayuda a mi camarada, y responderé a todas tus preguntas!";
			link.l1.go = "tonzag_bail_a";
			link.l2 = "¡¿Eres una persona tan importante, y viniste aquí sin ningún guardia, justo después de que toda la prisión escuchara un disparo?!";
			link.l2.go = "tonzag_bail_b";
		break;
		
		case "tonzag_bail_a":
			dialog.text = "Mientras demoras tu respuesta, él se está desangrando. Repito la pregunta.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_b":
			dialog.text = "Sé   bastante   sobre   lo   que   pasó.   Repito   la   pregunta.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "Última oportunidad, Capitán.";
			link.l1 = "¡Estoy llevando a cabo la tarea que me dio el gobernador general!";
			link.l1.go = "tonzag_bail_truth";
			link.l2 = "Sabes muy bien que soy el Capitán de mi propia nave, y trabajo por contrato. ¡Y visito tu encantadora isla unas cuantas veces al año!";
			link.l2.go = "tonzag_bail_lies";
		break;
		
		case "tonzag_bail_truth":
			dialog.text = "Tenía mis sospechas, pero no estaba completamente seguro. Tienes suerte de que hace solo unos días tuvo lugar una reunión importante en Capsterville. Algunas personas muy influyentes lograron llegar a un acuerdo. Por lo tanto, ya no eres mi enemigo.";
			link.l1 = "¿Nos ayudarás?";
			link.l1.go = "tonzag_bail_truth_1";
			
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
		case "tonzag_bail_truth_1":
			dialog.text = "Te liberaré de inmediato. Tu camarada será trasladado al barco y recibirá tratamiento.";
			link.l1 = "Gracias...";
			link.l1.go = "tonzag_bail_truth_2";
		break;
		
		case "tonzag_bail_truth_2":
			dialog.text = "¡Casi encallas, Charles! Vete y no regreses a Tortuga por al menos un mes. Deja que el polvo se asiente y las cabezas se enfríen.";
			link.l1 = "Haré eso. ¡Hasta luego!";
			link.l1.go = "exit";
			link.l2 = "¿No explicarás nada en absoluto? ¿Ni siquiera un poco? ...";
			link.l2.go = "tonzag_bail_truth_3";
		break;
		
		case "tonzag_bail_truth_3":
			dialog.text = "Alguien te denunció. Supuestamente, eres un católico fanático que llegó a nuestra hermosa isla para asesinar maliciosamente a su honorable gobernador.";
			link.l1 = "¡No soy un fanático!";
			link.l1.go = "tonzag_bail_truth_4";
		break;
		
		case "tonzag_bail_truth_4":
			dialog.text = "Está escrito hábilmente, créeme. Soy bueno en esas cosas: las mejores libelos son las que contienen al menos un grano de verdad en ellas.";
			link.l1 = "¿Quién escribió el informe?";
			link.l1.go = "tonzag_bail_truth_a";
			link.l2 = "¿Quién dejó entrar al asesino en la prisión?";
			link.l2.go = "tonzag_bail_truth_b";
		break;
		
		case "tonzag_bail_truth_a":
			dialog.text = "Alguien que quería que estuvieras encerrado en la prisión por unos días, en lugar de enviarte inmediatamente a la mesa de tortura de los hugonotes en el sótano de La Roche.\nBasta, Charles. Vete. Ocúpate primero de lo que tienes delante, y después... bueno, ¡me entiendes!";
			link.l1 = "Sí. Lo haré. Adiós, Comandante.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail_truth_b":
			dialog.text = "Lo hice.";
			link.l1 = "Será mejor que envíes por otro antes de que me vaya de aquí.";
			link.l1.go = "tonzag_bail_truth_b_threat";
			link.l2 = "Soy todo oídos, comandante.";
			link.l2.go = "tonzag_bail_truth_b_charm";
		break;
		
		case "tonzag_bail_truth_b_threat":
			AddComplexSelfExpToScill(100, 100, 100, 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "No estoy obligado a explicarte nada, Charles. Alégrate de haber caído en mis manos y no en las manos de mi superior directo. Y alégrate de que será tu jefe quien me compense por todas estas molestias, y no tú.";
				link.l1 = "Riiiiiiight... No conoces a mi jefe como yo. Hasta luego, comandante.";
				link.l1.go = "exit";
				
				notification("Skill Check Failed (60)", SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "¿Sabes qué? Creo que te lo diré. Se hizo una generosa donación, libre de impuestos, al fondo de pensiones especial de la guarnición. Como gesto de gratitud, se le permitió al donante contribuir a la rápida y legal ejecución de un notorio criminal.";
				link.l1 = "¿Mi oficial?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "¿Mi amigo?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				notification("Skill Check Passed", SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_charm":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "No estoy obligado a explicarte nada, Charles. Alégrate de que acabaste en mis manos y no en las de mi superior directo. Y alégrate de que sea tu jefe quien me compense por todas estas molestias, y no tú.";
				link.l1 = "Riiiiiiight... No conoces a mi jefe como yo. Hasta luego, comandante.";
				link.l1.go = "exit";
				
				notification("Skill Check Failed (60)", SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "¿Sabes qué? Creo que te lo diré. Se hizo una generosa donación, libre de impuestos, al fondo de pensiones especial de la guarnición. Como gesto de gratitud, se permitió al donante contribuir a la rápida y legal ejecución de un notorio criminal.";
				link.l1 = "¿Mi oficial?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "¿Mi amigo?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				notification("Skill Check Passed", SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_1":
			dialog.text = "Vete, Charles. Y llévate a esta escoria contigo. Tu elección de compañeros... es decepcionante.";
			link.l1 = "Al menos dime dónde encontrar a tu... benefactor.";
			link.l1.go = "tonzag_bail_truth_b_2";
		break;
		
		case "tonzag_bail_truth_b_2":
			dialog.text = "En el continente. Adiós, Charles.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.TonzagQuest.KnowMain = true;
			AddQuestRecord("Tonzag", "3.2");
		break;
		
		case "tonzag_bail_lies":
			dialog.text = "Se ha presentado un informe en tu contra. Uno muy desagradable. Capitán, evidentemente te han tendido una trampa, pero... estoy completamente dentro de mi autoridad para mantenerte aquí por un par de semanas más y dejar que tu amigo muera. A menos que...";
			link.l1 = "¿Cuánto?";
			link.l1.go = "tonzag_bail_lies_a";
			link.l2 = "¿Quién me tendió una trampa? ¿Dejaste que el asesino entrara en la prisión?";
			link.l2.go = "tonzag_bail_lies_b";
			
			AddDialogExitQuestFunction("Tonzag_Bailed");
		break;
		
		case "tonzag_bail_lies_a":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Por favor, deposita quinientos doblones en el fondo de pensiones de la guarnición de Tortuga con el prestamista.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+" Y agreguemos otros cien doblones por los viejos problemas que causaste al involucrarte con una dama de alto rango en esta isla.";
			}
			link.l1 = "¡Abre ya esta maldita puerta!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bail_lies_b":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Ya has ocupado demasiado de mi tiempo. Ve al prestamista y deposita quinientos doblones en el fondo de pensiones de la guarnición de Tortuga.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+" Y añadamos otros cien doblones por los viejos problemas que causaste al involucrarte con una dama de alto rango en esta isla.";
			}
			link.l1 = "¡Abre esta maldita puerta de una vez!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bailed":
			dialog.text = "";
			link.l1 = "Los fondos están depositados. ¿Dónde está Hercule?";
			link.l1.go = "tonzag_bailed_1";
		break;
		
		case "tonzag_bailed_1":
			dialog.text = "Le proporcionamos primeros auxilios y lo enviamos a su barco. El canalla es duro, lo más probable es que salga adelante. ¡Adiós, Capitán, y no dejes que te pille en nuestra isla por un tiempo!";
			link.l1 = "Bueno, después de tal recibimiento, ¡me mantendré bien alejado de aquí! Adiós, comandante.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
