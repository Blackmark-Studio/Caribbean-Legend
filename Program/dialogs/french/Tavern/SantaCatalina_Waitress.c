// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Questions, "+GetAddress_Form(NPChar)+"?","Comment puis-je vous aider, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Hm, quelle est cette grande idée, "+GetAddress_Form(NPChar)+"? ","Encore avec tes questions étranges ? Toots, va te chercher un rhum ou quelque chose...")+"","Pendant toute cette journée, c'est la troisième fois que tu parles d'une question..."+GetSexPhrase(" Sont-ce des signes d'attention ?"," ")+"","Encore des questions, je présume, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis","Je n'ai rien à dire pour le moment."),"Non, non belle...","Aucune chance, ma chère...","Non, quelles questions?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "helendrinking":
			dialog.text = "Comment avez-vous dormi, monsieur ? Mademoiselle MacArthur nous a ordonné d'assurer votre plein confort !";
			link.l1 = "J'ai fait un rêve très étrange...";
			link.l1.go = "helendrinking_1";
		break;

		case "helendrinking_1":
			dialog.text = "Ah!...";
			link.l1 = "Quel est le problème, mademoiselle ? Puis-je vous aider avec quelque chose ?";
			link.l1.go = "helendrinking_2";
		break;

		case "helendrinking_2":
			dialog.text = "Je suis désolée, Capitaine... C'est un péché, mais je ne peux pas résister ! Je ne suis pas très expérimentée, mais ne refusez pas la fille, Capitaine ! Vous êtes si beau ! Je veux vous plaire, vous toucher...";
			link.l1 = "En effet, tout le confort... Vous êtes aussi très belle ! Allez, ne soyez pas timide.";
			link.l1.go = "helendrinking_sex";
			link.l2 = "Il vaut mieux ne pas me toucher en ce moment, mademoiselle - je pue le rhum. Mais vous pouvez me faire plaisir - un petit-déjeuner serait très apprécié !";
			link.l2.go = "helendrinking_nosex";
		break;
		
		case "helendrinking_sex":
			dialog.text = "Oh là là, oh là là!";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressSex");
		break;

		case "helendrinking_nosex":
			dialog.text = "Grossier !";
			link.l1 = "Pas de petit-déjeuner alors ?";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			Notification_Approve(true, "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressNoSex");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
