// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular?","Ne istiyorsun, "+GetAddress_Form(NPChar)+"?"),"Bana zaten bir soru sormaya çalıştın "+GetAddress_Form(NPChar)+"...","Bugün bu soruyu üçüncü kez gündeme getiriyorsunuz...","Bak, eğer limanın işleriyle ilgili bana söyleyecek bir şeyin yoksa, o zaman sorularınla beni meşgul etme.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim.","Konuşacak bir şeyim yok."),"Boşver.","Gerçekten de, üçüncü kez oldu artık...","Üzgünüm, ama şimdilik limanın işlerine ilgim yok.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (pchar.questTemp.Slavetrader == "FindRatTortuga")
            {
                link.l1 = "İyi günler. Francois Gontier'i arıyorum. Onun korveti '"+pchar.questTemp.Slavetrader.ShipName+"' limanınızda olmalıydı.";
                link.l1.go = "Tortuga_ratP_1";
            }
			
		break;

		case "Tortuga_ratP_1":
			dialog.text = NPCStringReactionRepeat("Hm... Sizi hayal kırıklığına uğratmak zorundayım. Korvet '"+pchar.questTemp.Slavetrader.ShipName+" buraya hiç gelmedi ve Francois Gontier de burada kayıtlı değil.","Bunu zaten sordunuz ve ben de cevapladım.","Sana söyledim, bu Gontier hakkında zaten sormuştun.","Lütfen, beni işimden alıkoyma!","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Teşekkürler. Aramaya devam edeceğim.","Hm, şey...","Evet, gerçekten sordum ...","Affedersiniz, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
