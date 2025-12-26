// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Bana bu soruyu kısa bir süre önce de sormuştunuz...","Evet, dur tahmin edeyim... Yine aynı şeyleri mi dönüp duruyorsun?","Bakın, burada finans işlerini ben yürütüyorum, sorulara cevap vermem...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Doğru tahmin ettiniz, üzgünüm...","Anlıyorum...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail":
			dialog.text = "Merhaba, Kaptan. Firmam ve ben size nasıl yardımcı olabiliriz?";
			link.l1 = "Tortuga'nın seçkin garnizonunun emeklilik fonuna bağış yapmak istiyorum.";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "Anlıyorum. Son zamanlarda oldukça popüler oldunuz! Ne kadar borcunuz var... yani, ne kadar bağışlamak istersiniz?";
			link.l1 = pchar.questTemp.TonzagQuest.Bail+" doblon. Söyleyin, peso kabul ediyor musunuz?";
			link.l1.go = "tonzag_bail_2";
		break;
		
		case "tonzag_bail_2":
			dialog.text = "Elbette, ancak bu size biraz daha pahalıya mal olacak. Size tam olarak söyleyeyim... "+pchar.questTemp.TonzagQuest.Bail+" dublon olacak "+sti(pchar.questTemp.TonzagQuest.Bail)* 150+" peso.";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.TonzagQuest.Bail) || sti(pchar.money) >= sti(pchar.questTemp.TonzagQuest.Bail) * 150) {
				link.l1 = "Biraz daha pahalı mı diyorsunuz? Buyurun, gereken tutarın tamamı burada.";
				link.l1.go = "tonzag_bail_give";
			} else {
				link.l1 = "Biraz daha pahalı mı diyorsunuz? Ne yazık ki şu anda o kadar param yok. Bu iş için kredi çekmem mümkün mü?";
				link.l1.go = "tonzag_bail_loan";
			}
		break;
		
		case "tonzag_bail_give":
			dialog.text = "Harika. Karşı tarafı hemen bilgilendireceğiz! Hoşça kalın, Kaptan. Ve... iyi şanslar, sizin performansınızı uzun zamandır merakla bekliyorduk.";
			link.l1 = "Hoşça kal.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			if (PCharDublonsTotal() >= sti(pchar.questTemp.TonzagQuest.Bail)) {
				RemoveDublonsFromPCharTotal(sti(pchar.questTemp.TonzagQuest.Bail));
			} else {
				AddMoneyToCharacter(pchar, -(sti(pchar.questTemp.TonzagQuest.Bail) * 150));
			}
			sld = CharacterFromID("TortugaJailOff");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "tonzag_bailed";
		break;
		
		case "tonzag_bail_loan":
			dialog.text = "Böyle bir fırsat size her zaman açıktır, Kaptan! Diyelim ki, altı ay içinde iki yüz bin peso geri ödemek şartıyla?";
			link.l1 = "Başka seçeneğim yok. Nerede imzalayacağım?";
			link.l1.go = "tonzag_bail_give";
			
			pchar.quest.loans.tortuga.sum = 200000;
			pchar.quest.loans.tortuga.interest = 0;
			pchar.quest.loans.tortuga.period = 6;
			pchar.quest.loans.tortuga.StartDay = GetDataDay();
			pchar.quest.loans.tortuga.StartMonth = GetDataMonth();
			pchar.quest.loans.tortuga.StartYear = GetDataYear();
			pchar.quest.loans.tortuga.StartTime = GetTime();
			SetTimerCondition("Loans_Tortuga", 0, makeint(pchar.quest.loans.tortuga.period), 0, false);
			pchar.quest.Loans_Tortuga.CityId = "Tortuga";
			pchar.quest.Loans_Tortuga.win_condition = "LoansForAll";
			
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.TonzagQuest.Bail) * 150);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
