// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Preguntas, "+GetAddress_Form(NPChar)+"?","¿En qué puedo ayudarle, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Mm, ¿cuál es la gran idea, "+GetAddress_Form(NPChar)+"? ","¿Otra vez con las preguntas extrañas? Chiquillo, ve a tomar un poco de ron o algo...")+"Hola, capitán.","Durante todo este día, esta es la tercera vez que hablas de alguna pregunta..."+GetSexPhrase(" ¿Son estas algunas señales de atención?","")+"","¿Más preguntas, supongo, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión","No tengo nada de qué hablar en este momento."),"No, no hermosa...","No querida...","No, ¿qué preguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "helendrinking":
			dialog.text = "¿Cómo durmió, monsieur? ¡La señorita MacArthur nos ordenó asegurarle el máximo confort!";
			link.l1 = "Tuve un sueño muy extraño...";
			link.l1.go = "helendrinking_1";
		break;

		case "helendrinking_1":
			dialog.text = "¡Ah!...";
			link.l1 = "¿Qué pasa, mademoiselle? ¿Puedo ayudarle con algo?";
			link.l1.go = "helendrinking_2";
		break;

		case "helendrinking_2":
			dialog.text = "Lo siento, capitán... Es un pecado, ¡pero no puedo resistir! No tengo mucha experiencia, ¡pero no rechaces a esta chica, capitán! ¡Eres tan apuesto! Quiero complacerte, tocarte...";
			link.l1 = "En verdad, pleno confort... ¡También eres muy hermosa! Vamos, no seas tímida.";
			link.l1.go = "helendrinking_sex";
			link.l2 = "Es mejor no tocarme ahora, mademoiselle, apesto a ron. ¡Pero puedes complacerme, un desayuno sería muy bienvenido!";
			link.l2.go = "helendrinking_nosex";
		break;
		
		case "helendrinking_sex":
			dialog.text = "¡Oh cielos, oh cielos!";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			notification("¡Helen lo desaprueba!", "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressSex");
		break;

		case "helendrinking_nosex":
			dialog.text = "¡Grosero!";
			link.l1 = "¿Entonces no hay desayuno?";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			notification("¡Helen lo aprueba!", "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressNoSex");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
