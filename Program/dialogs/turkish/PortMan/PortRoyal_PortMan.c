// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular?","Ne istiyorsun, "+GetAddress_Form(NPChar)+"?"),"Bana zaten bir soru sormaya çalıştın "+GetAddress_Form(NPChar)+"...","Bu soruyu bugün üçüncü kez gündeme getiriyorsunuz...","Bak, eğer limanın işleriyle ilgili bana söyleyecek bir şeyin yoksa, sorularınla beni meşgul etme.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim.","Konuşacak bir şeyim yok."),"Boşver.","Gerçekten de, bu üçüncü sefer zaten...","Üzgünüm, ama şimdilik limanın işlerine ilgim yok.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Günaydın. Kaptan François Gontier burada kayıt yaptırdı mı? Porto Bello'dan ' adlı korvetle yola çıkmıştı."+pchar.questTemp.Slavetrader.ShipName+"'.";
                link.l1.go = "Jamaica_ratPP_1";
            }
			
		break;
		
		case "Jamaica_ratPP_1":
			dialog.text = NPCStringReactionRepeat("Hayır, etmedi. Ve korvet '"+pchar.questTemp.Slavetrader.ShipName+"' Port Royal'de görülmedi.","Bunu zaten sordunuz ve ben de cevapladım.","Sana bu Gontier denen adamı zaten sorduğunu söylemiştim.","Lütfen, işimden beni alıkoyma!","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Teşekkürler. Aramaya devam edeceğim.","Hm, şey...","Evet, gerçekten sordum ...","Affedersiniz, "+npchar.name+"...",npchar,Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
