// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Sorular, "+GetAddress_Form(NPChar)+"?","Size nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Hm, neyin peşindesin, "+GetAddress_Form(NPChar)+"? ","Yine tuhaf sorularla mı geldin? Canım, git biraz rom iç ya da başka bir şey yap...")+"","Bugün içinde bu soruyu üçüncü kez gündeme getiriyorsun..."+GetSexPhrase(" Bunlar bir ilgi göstergesi mi?","")+"","Sanırım yine sorularınız var. "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim","Şu anda konuşacak bir şeyim yok."),"Hayır, güzel değil...","Olmaz, canım...","Hayır, ne soruları?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "helendrinking":
			dialog.text = "Nasıl uyudunuz, monsieur? Bayan MacArthur, sizin tam konforunuz için her şeyi sağlamamızı emretti!";
			link.l1 = "Çok garip bir rüya gördüm...";
			link.l1.go = "helendrinking_1";
		break;

		case "helendrinking_1":
			dialog.text = "Ah!...";
			link.l1 = "Ne oldu, madam? Size bir konuda yardımcı olabilir miyim?";
			link.l1.go = "helendrinking_2";
		break;

		case "helendrinking_2":
			dialog.text = "Üzgünüm, Kaptan... Günah biliyorum, ama kendimi tutamıyorum! Çok tecrübeli değilim, ama beni geri çevirme, Kaptan! Çok yakışıklısın! Sana zevk vermek, sana dokunmak istiyorum...";
			link.l1 = "Gerçekten, tam bir konfor... Ayrıca çok güzelsin! Hadi, çekinme.";
			link.l1.go = "helendrinking_sex";
			link.l2 = "Şu anda bana dokunmasan iyi olur, mademoiselle – rom kokuyorum. Ama beni memnun edebilirsin – güzel bir kahvaltı harika olurdu!";
			link.l2.go = "helendrinking_nosex";
		break;
		
		case "helendrinking_sex":
			dialog.text = "Aman Tanrım, aman Tanrım!";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressSex");
		break;

		case "helendrinking_nosex":
			dialog.text = "Kaba!";
			link.l1 = "Kahvaltı yok mu yani?";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			Notification_Approve(true, "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressNoSex");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
