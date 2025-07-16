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
		
		//--> Тайна Бетси Прайс
		case "TBP_BetsiPriceSex1":
			DoFunctionReloadToLocation("Villemstad_tavern_upstairs", "quest", "quest4", "TBP_Betsi_sex_2");
		break;
		//<-- Тайна Бетси Прайс
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
