// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular?","Ne istiyorsun, "+GetAddress_Form(NPChar)+"?"),"Bana zaten bir soru sormaya çalıştınız "+GetAddress_Form(NPChar)+"...","Bugün bu soruyu üçüncü kez gündeme getiriyorsunuz...","Bakın, eğer limanın işleriyle ilgili bana söyleyecek bir şeyiniz yoksa, sorularınızla beni meşgul etmeyin.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim.","Konuşacak bir şeyim yok."),"Boşver.","Gerçekten de, üçüncü kez oldu artık...","Üzgünüm, ama şimdilik liman işleriyle ilgilenmiyorum.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// НСО пошив мундира Xenon-->
		case "Tailor":
			dialog.text = "Evet, sizi gayet iyi anlıyorum, bağırmanıza gerek yok. Ama zaten açıkladım – bu sefer her zamankinden çok daha fazla yazışma ve posta vardı. Merak etmeyin, evraklarınız kaybolmayacak ve bir sonraki kurye gemisiyle teslim edilecek.";
			link.l1 = "...";
			link.l1.go = "Tailor_01";
		break;
		
		case "Tailor_01":
			DialogExit();
			sld = characterFromId("Patria_Tailor");
			sld.dialog.currentnode = "Tailor_02";
			Lai_SetPlayerType(pchar);
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "Tailor_02":
			dialog.text = "Bakın, belli ki daha önemli paketler vardı. Ayrıca gemi fazla yüklenemez. Ancak, postaların nasıl dağıtıldığı hakkında bana bilgi verilmedi. Lütfen sakin olun ve telaşlanmayın. Tekrar ediyorum: tüm eşyalarınız eksiksiz ulaşacak, sadece biraz gecikecek.";
			link.l1 = "...";
			link.l1.go = "Tailor_03";
		break;
		
		case "Tailor_03":
			npchar.dialog.currentnode = "First time";
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Patria_Tailor");
			sld.dialog.currentnode = "Tailor_04";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		// <-- пошив мундира
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
