// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne istiyorsunuz? Sorunuzu sorun.","Dinliyorum, sorun nedir?"),"Bu ikinci kez sormaya çalışıyorsun...","Bu üçüncü kez sormaya çalışıyorsunuz...","Bu ne zaman bitecek?! Ben meşgul bir adamım, koloni işleriyle uğraşıyorum, sen ise hâlâ beni rahatsız ediyorsun!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim, üzgünüm.","Şimdi değil. Yeri ve zamanı değil."),"Doğru, şu anda söyleyecek bir şeyim yok, üzgünüm.","Daha sonra soracağım.","Üzgünüm, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Zaten her şeyi aldınız. Daha ne istiyorsunuz?","Almadığın bir şey kaldı mı?");
            link.l1 = RandPhraseSimple("Sadece etrafa bakıyorum...","Sadece kontrol ediyorum, bir şeyi almayı unutmuş olabilirim...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
