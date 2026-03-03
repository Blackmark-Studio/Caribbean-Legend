// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Perguntas, "+GetAddress_Form(NPChar)+"?","Como posso ajudar você, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Hm, qual é a sua, "+GetAddress_Form(NPChar)+"? ","De novo com essas perguntas estranhas? Querido, vai tomar um rum ou algo assim...")+"","No decorrer deste dia, esta é a terceira vez que você levanta essa questão..."+GetSexPhrase(" Isso são sinais de carinho?","")+"","Mais perguntas, imagino. "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia","Não tenho nada para conversar no momento."),"Não, não é bonito...","De jeito nenhum, querido...","Não, que perguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "helendrinking":
			dialog.text = "Como dormiu, monsieur? A senhorita MacArthur nos pediu para garantir o seu total conforto!";
			link.l1 = "Eu tive um sonho muito estranho...";
			link.l1.go = "helendrinking_1";
		break;

		case "helendrinking_1":
			dialog.text = "Ah!...";
			link.l1 = "O que houve, mademoiselle? Posso ajudar em alguma coisa?";
			link.l1.go = "helendrinking_2";
		break;

		case "helendrinking_2":
			dialog.text = "Me desculpe, Capitão... É um pecado, mas eu não consigo resistir! Não tenho muita experiência, mas não me rejeite, Capitão! Você é tão bonito! Quero te agradar, te tocar...";
			link.l1 = "De fato, total conforto... E você também é muito bonita! Vamos lá, não precisa ter vergonha.";
			link.l1.go = "helendrinking_sex";
			link.l2 = "É melhor não me tocar agora, mademoiselle – estou fedendo a rum. Mas pode me agradar – um café da manhã seria muito bem-vindo!";
			link.l2.go = "helendrinking_nosex";
		break;
		
		case "helendrinking_sex":
			dialog.text = "Ai, ai!";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressSex");
		break;

		case "helendrinking_nosex":
			dialog.text = "Grosseiro!";
			link.l1 = "Sem café da manhã então?";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			Notification_Approve(true, "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressNoSex");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
