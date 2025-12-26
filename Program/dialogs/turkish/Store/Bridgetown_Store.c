// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Devam et, ne istiyorsun?","Biz de tam bundan bahsediyorduk. Herhalde unuttunuz...","Bugün bu soruyu üçüncü kez gündeme getiriyorsunuz...","Bakın, burası bir dükkân. İnsanlar burada alışveriş yapar. Beni rahatsız etmeyin!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Biliyor musun, "+NPChar.name+", belki bir dahaki sefere.","Evet, nedense unuttum...","Evet, gerçekten de üçüncü kez...","Hm, yapmayacağım...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Bakın, küçük bir kuş bana Belize'de sekoya ve kakao fiyatlarının yakında fırlayacağını söyledi. Son zamanlarda iyi bir iş yaptım ve kesemi doblonlarla doldurdum, hehe... Bu mallardan biraz almak istiyorum. Bir indirim yapabilir misiniz?";
                link.l1.go = "StoreDone";
            }
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados1")
			{
				link.l1 = "‘Admirable’ adında bir kalyon kısa süre önce Kaptan Gaius Marchais komutasında koloninize demirledi. Söyler misiniz, burada mühimmat ya da satmak için ticari mal almış olabilir mi?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "StoreDone":
			dialog.text = "Efendim, eğer parti gerçekten büyükse, elbette makul bir indirim konuşabiliriz.";
			link.l1 = "Harika! Tersanede yakında yeni bir fluyt satışa çıkacak diye duydum. Bekleyip o gemiyi alacağım. Brigimdeki tüm topları çıkarmama rağmen, ambarımda bu kadar mal için hâlâ yeterli yer yok! Sonra tekrar uğrarım!";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-11");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Ha! O tuhaf adamı hatırlıyorum! Guadeloupe'un vanilyaya çok ihtiyaç duyacağına dair saçma bir dedikoduya inanmıştı; çünkü Avrupalı tüccarların büyük bir kervanı oraya uğrayıp taşıyabildikleri kadar baharat alacaklarmış\nBöyle saçmalıkları her ay duyarım ama Marchais bunu çok ciddiye aldı. Burada bir hafta kaldı, bana ambarlarını dolduracak kadar vanilya toplamamı söyledi\nGörünüşe göre elindeki tüm parayı buna harcamış. Adam için üzülüyorum ama bir adam delirmek isterse onu durduramam.";
			link.l1 = "Yani, şu anda Guadeloupe'da olabilir mi?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Büyük ihtimalle. Çünkü hayali 'tüccarlarını' bekleyip duracak, ta ki Mesih'in ikinci gelişine kadar, ve vanilya satarken sadece zarar edecek. Akıllıysa, vanilyaya olan talep fırlayana ya da başka bir yerde daha çok ihtiyaç olduğundan emin olana kadar Basse-Terre'de kalır.";
			link.l1 = "Evet. Teşekkür ederim, bana çok yardımcı oldunuz!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "14");
			pchar.questTemp.Guardoftruth = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1 = "location";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1.location = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.function = "GuardOT_CreateTwoShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
