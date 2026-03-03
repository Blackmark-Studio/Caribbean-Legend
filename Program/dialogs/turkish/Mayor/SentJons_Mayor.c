// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne istiyorsunuz? Sorunuzu sorun.","Dinliyorum, sorunuz nedir?"),"Bu ikinci kez sormaya çalışıyorsun...","Bu, üçüncü kez sormaya çalıştığınız oldu...","Bu ne zaman bitecek?! Ben meşgul bir adamım, koloni işleriyle uğraşıyorum ve sen hâlâ beni rahatsız ediyorsun!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şimdi değil. Yeri ve zamanı değil"),"Doğru... Ama sonra, şimdi değil...","Soracağım... Ama biraz sonra...","Üzgünüm, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "antigua")
			{
				link.l1 = "Ekselansları, size Mercury'nin kayboluşuyla ilgili bazı bilgilere sahip olduğumu bildirmek isterim.";
                link.l1.go = "G_Girl";
			}
		break;
		
		// Jason Дороже золота
		case "G_Girl":
			dialog.text = "Bilgi mi? Yine ne hakkında?";
			link.l1 = "Brigantin, Ekselansları. Posta taşıyor. Önemli belgeler ve benzeri şeyler. Soruşturmayı duydum ve tabii ki, Britanya Kraliyeti'nin sadık bir dostu olarak, yardımcı olmak isterim.";
			link.l1.go = "G_Girl_1";
		break;
		
		case "G_Girl_1":
			dialog.text = "Harika! Baronet Cortney sizi ağırlamaktan büyük mutluluk duyacaktır! Hemen bir görüşme ayarlayacağım.";
			link.l1 = "Teşekkür ederim, efendim. Burada acelem var ve bunun hızlıca halledilmesini takdir ederim.";
			link.l1.go = "G_Girl_2";
		break;
		
		case "G_Girl_2":
			dialog.text = "Endişelenmeyin, vaktiniz bol olacak. Muhafızlar! Onu yakalayın!";
			link.l1 = "Teşekkürler... bekle, ne? Bu bir şaka mı?!";
			link.l1.go = "G_Girl_3";
		break;
		
		case "G_Girl_3":
			DialogExit();
			GoldenGirl_AntiguaArest();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
