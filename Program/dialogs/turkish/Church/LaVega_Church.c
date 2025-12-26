// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular, "+GetSexPhrase("evladım","kızım")+"?","Sor bakalım, dinliyorum..."),"Dinliyorum, şimdi konuş. "+GetSexPhrase("evladım","kızım")+"...","Üçüncü kez, "+GetSexPhrase("evladım","kızım")+", neye ihtiyacın varsa sor.","Bir din adamının yapacak çok işi var ve sen beni oyalıyorsun, "+GetSexPhrase("evladım","kızım")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda değil, padre..."),"Söyleyecek bir şeyim yok, özür dilerim.","Soracağım, ama sonra. Beni affedin, baba.","Affedersiniz, kutsal baba...",npchar,Dialog.CurrentNode);
		    link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
