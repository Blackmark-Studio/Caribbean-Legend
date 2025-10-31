// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?","How can I help you?"),"You tried to ask me that question not long ago...","Yup, let me guess... Going around in circles again?","Listen, I handle the finances here, I don't answer questions...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...","I've got nothing to talk about at the moment."),"Umph, where has my memory gone...","You've guessed it, I'm sorry...","I understand...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// Реакция ростовщика Панамы на репутацию ГГ или на разграбление Картахены по сюжету
		case "Panama_Deposit_NoReputation":
			dialog.text = "That's right... A man of honour who is loved by the King's subjects will never be refused by my bank, no matter what his nationality.";
			link.l1 = "I understand. Goodbye.";
			link.l1.go = "exit";
		break;
		
		case "Panama_Deposit_Cartahena":
			dialog.text = "But my daughter and father-in-law caught it, unfortunately. They lived in Cartagena. Go away, "+GetAddress_Form(NPChar)+". You are not welcome here.";
			if (pchar.questTemp.Mtraxx.Retribution.Choice == "good")
			{
				link.l1 = "Forgive me. Farewell.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Your loss. Goodbye.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
		
		case "Panama_Deposit_SgorelVklad":
			dialog.text = "The funds were seized by the Crown to aid the victims of the sacking of the city of Cartagena. I can't help you. I'm going to ask you to leave my bank immediately before I call the guards!";
			link.l1 = "You're going to regret this...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
