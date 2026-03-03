// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Ne tür sorular?","Ne istiyorsun?");
			link.l1 = RandPhraseSimple("Fikrimi değiştirdim.'","Şu anda söyleyecek bir şeyim yok.");
		    link.l1.go = "exit";
		break;
		
		case "info":
			dialog.text = LinkRandPhrase("Kiminle ilgileniyorsun?","Kimi kastediyorsun?","Peki, kimmiş?");
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				link.l1 = "Jan Svenson hakkında daha fazla bilgi almak istiyorum.";
				link.l1.go = "svenson";
			}
			link.l2 = "Konu değiştirelim...";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("Nereye gitmek istiyorsun?","Ne arıyorsun?","Tam olarak neye ihtiyacınız var?");
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				link.l1 = "Jan Svenson'un evi nerede?";
				link.l1.go = "svenson_house";
			}
			link.l2 = "Konu değiştirelim...";
			link.l2.go = "new question";
		break;
		
		case "svenson":
			dialog.text = RandPhraseSimple("Ah, bizim Jan Svenson çok önemli bir adamdır. Eskiden Batı Ana'nın en gözde korsanıydı ve hâlâ paslanmaya başlamadı, ha! Ama o günler geride kaldı, artık eskisi kadar aktif değil. Bir malikanesi var, genç eşiyle orada yaşıyor ve her zaman valinin konağında hoş karşılanır. Jan'a çok misafir gelir, çoğu da korsanlardan oluşur.","Jan Svenson Batı Ana'nın efsanesidir! Orman Şeytanı, İspanyollar ona buradan onları kovarken böyle derlerdi. Eskiden ünlü bir korsandı, ama şimdi kolonimizin saygın bir vatandaşı.\nYine de hâlâ biraz 'iş' çeviriyor, ama artık bizzat kendisi yapmıyor. Genç bir güzelle evlendikten sonra evinden pek çıkmaz oldu.");
			link.l1 = "Teşekkür ederim.";
			link.l1.go = "exit";
		break;
		
		case "svenson_house":
			dialog.text = RandPhraseSimple("İskeleden dümdüz gidin, meydana vardığınızda sağdaki, çeşmenin yanındaki ev Svenson'un malikanesi.","Valinin konutundan meydana doğru gidip iskeleye ulaş, çeşmenin yanındaki soldaki ev Svenson'un malikanesi.");
			link.l1 = "Teşekkür ederim.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
