// диалоги обитателей плантаций
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, i, n;
	string sTemp;
	bool bOk;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Bir şeye ihtiyacın var mı?";
			link.l1 = "Hayır, istemiyorum.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// рабы
		case "plantation_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("O kadar yorgunum ki, neredeyse düşeceğim...","Böyle yaşanmıyor artık!"),RandPhraseSimple("Bu iş beni öldürüyor."," Muhafızlar hepimizi öldürmek istiyor! "));				
			link.l1 = RandPhraseSimple("Ne yazık.","Üzgünüm.");
			link.l1.go = "exit";				
		break;
		
		// рабы-пираты по пиратской линейке
		case "pirate_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Dinle, git buradan!","Defol!"),RandPhraseSimple("Ne istiyorsun?!","Defol git buradan!"));				
			link.l1 = RandPhraseSimple("Hm...","Pekâlâ...");
			link.l1.go = "exit";				
		break;
		
		// охрана - солдаты
		case "plantation_soldier":
            dialog.text = RandPhraseSimple(RandPhraseSimple("Git, plantasyonun başını rahatsız et","Kölelerin dikkatini dağıtma, dostum."),RandPhraseSimple("Benim işim bu tembel herifleri motive etmek.","Lanet olsun, bugün de çok sıcak, her zamanki gibi..."));
			link.l1 = RandPhraseSimple("Anladım...","Gerçekten...");
			link.l1.go = "exit";
		break;
		
		// охрана - протектор
		case "plantation_protector":
            if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if (sti(pchar.nation) == PIRATE)
				{
					PlaySound("Voice\English\soldier_arest_1.wav");
    				dialog.text = RandPhraseSimple(" Korsan mı?! Onu yakalayın!","O bir korsan! Saldırın!");
					link.l1 = RandPhraseSimple("Korsan. Ee, ne olmuş?","Heh, devam et ve dene bakalım.");
					link.l1.go = "fight"; 
					break;
				}
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = RandPhraseSimple("Ho-ho, sen şu bayrak altında yol alıyorsun: "+NationNameGenitive(sti(pchar.nation))+"! Komutanımızın sizinle konuşmaktan memnun olacağını düşünüyorum!","Pekala, pekala, burası kokuyor "+NationNameAblative(sti(pchar.nation))+" burada! Bir casus mu?! Komutanımızla konuşma vaktin geldi.");
				link.l1 = RandPhraseSimple("Önce seni cehenneme göndereceğim!","Artık kılıcımla konuşma vaktin geldi!");
				link.l1.go = "fight"; 
			}
			else
			{
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					if (sti(pchar.nation) == PIRATE)
					{
						PlaySound("Voice\English\soldier_arest_1.wav");
						dialog.text = RandPhraseSimple(" Korsan mı?! Yakalayın onu!","O bir korsan! Saldırın!");
						link.l1 = RandPhraseSimple("Korsan mı!? Nerede?","Heh, devam et ve dene.");
						link.l1.go = "fight"; 
						break;
					}
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("Sen kimsin ve burada ne istiyorsun?","Dur! Burada ne işin var?");
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Bu yerin başıyla iş konuşmak istiyorum. Ticaret ruhsatım var.";
						link.l1.go = "Licence";
					}
					else
					{
						link.l1 = "Bu yerin başıyla iş konuşmak istiyorum.";
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50))) link.l1.go = "PegYou";
						else link.l1.go = "NotPegYou";
					}
					if (IsCharacterPerkOn(pchar, "Trustworthy"))
					{
						link.l2 = "(Güvenilir) Saygıdeğer señores, adil ve karşılıklı fayda sağlayacak bir ticaret için buradayım. Lütfen, plantasyon sahibini görmeme izin verin.";
						link.l2.go = "mtraxx_soldier_1";
						Notification_Perk(true, "Trustworthy");
					}
				}
				else
				{
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("Sen kimsin ve burada ne istiyorsun?","Dur! Burada ne işin var?");
					link.l1 = "Burada yetkili olan kişiyle iş konuşmak istiyorum.";
					link.l1.go = "NotPegYou";
				}
			}
		break;
		
		case "Licence":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = "Bir lisans mı? Bir saniye... Ha-ha, bu komik! Kim olduğunu biliyorum. Aranıyorsun, dostum! Ve başına konan ödül çok büyük! Yakala onu!";
				link.l1 = RandPhraseSimple("O halde kılıcımla tanışman gerekecek!","Siktir git.");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				PlaySound("Voice\English\soldier_arest_1.wav");
				dialog.text = "Bakalım... ha! Ruhsatınızın süresi dolmuş. O halde beni takip edin, sizi komutana götüreceğim...";
				link.l1 = RandPhraseSimple("Kahretsin! Sanırım artık kılıcımla tanışma vaktin geldi, dostum.","Bence öyle değil...");
				link.l1.go = "fight";	
				break;
			}
			dialog.text = "Pekala. İçeri girebilirsin. Uslu dur ve kölelere bulaşma.";
			link.l1 = "Endişelenme, dostum.";
			link.l1.go = "plantation_exit";
		break;
		
		case "PegYou":
			PlaySound("Voice\English\soldier_arest_2.wav");
            dialog.text = "İş mi? Ha-ha! Bu gerçekten komik! Üzerinden gelen koku ise "+NationNameAblative(sti(GetBaseHeroNation()))+" binlerce mil öteden! Artık komutanımızla tanışma vakti.";
			link.l1 = "Yok, bence artık kılıcımla tanışma vaktin geldi.";
			link.l1.go = "fight";
		break;
		
		case "NotPegYou":
            dialog.text = "Peki. İçeri girebilirsin. Uslu dur ve kölelere bulaşma.";
			link.l1 = "Endişelenme, dostum.";
			link.l1.go = "plantation_exit";
		break;
		
		case "plantation_exit":
           DialogExit();
		   NextDiag.CurrentNode = "plantation_repeat";
		break;
		
		case "plantation_repeat":
            dialog.text = "Hadi, yürü devam et!";
			link.l1 = "...";
			link.l1.go = "plantation_exit";
		break;
		
		// управляющий в Маракайбо // Addon 2016-1 Jason
		case "Plantator":
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_2") // belamour legendary edition 
			{
				dialog.text = "Burada ne işiniz var, señor?";
				link.l1 = TimeGreeting()+", señor. Size bir iş teklifim var. Satacak kölelerim var. "+FindRussianQtyString(sti(GetSquadronGoods(pchar,GOOD_SLAVES)))+" . İlgileniyor musun?";
				link.l1.go = "mtraxx";
				break;
			}
            dialog.text = "Burada ne işiniz var, señor?";
			link.l1 = "Sadece dolaşıyordum, bir merhaba demek istedim.";
			link.l1.go = "plantator_x";
		break;
		
		case "plantator_x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator";
		break;
		
		case "plantator_1":
			bOk = GetSquadronGoods(pchar, GOOD_COFFEE) >= 500 || GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500 || GetSquadronGoods(pchar, GOOD_COPRA) >= 500;
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup") && bOk) //пробуем выкупить Красавчика
			{
				dialog.text = "Yine sen, señor. Nasılsın?";
				link.l1 = "I have a business proposal for you. You produce sugar and cacao. I'd like to purchase your goods, but not with money; I can offer my own goods in exchange. Perhaps we could strike a bargain?";
				link.l1.go = "mtraxx_5";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_6" && bOk)
			{
				dialog.text = "Yine sen, señor. Nasılsın?";
				link.l1 = "I have a business proposal for you. You produce sugar and cacao. I'd like to purchase your goods, but not with money; I can offer my own goods in exchange. Perhaps we could strike a bargain?";
				link.l1.go = "mtraxx_5";
				break;
			}
            dialog.text = "Yine sen, señor. Nasılsın?";
			link.l1 = "Teşekkürler, iyiyim.";
			link.l1.go = "plantator_1x";
		break;
		
		case "plantator_1x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator_1";
		break;
		
		case "mtraxx":
			// belamour legendary edition возможность обмануть плантатора -->
			if(GetSquadronGoods(pchar, GOOD_SLAVES) >= 50 || CheckCharacterPerk(pchar, "Trustworthy") || ChangeCharacterHunterScore(Pchar, "spahunter", 0) <= -50)
			{
            dialog.text = "Sizi hayal kırıklığına uğratmak zorundayım, señor, ama şu anda köleye ihtiyacımız yok. Kaptan Eduardo de Losada, son baskınında yakaladığı korsanları bize çoktan sağladı.";
			link.l1 = "Burada korsanlar mı var? Burada nasıl uyuyabiliyorsun?";
			link.l1.go = "mtraxx_1";
			}
			else
			{
				dialog.text = "Ah, bakalım şimdi... Kölelerini satın alacağım. Ama bana öyle geliyor ki, sen kendini tanıttığın kişi değilsin. Gel benimle komutanın ofisine, sevgili dostum, eğer yanılıyorsam, sana tüm zahmetini fazlasıyla ödeyeceğim. Ve şimdi, affına sığınıyorum. Muhafız!";
				link.l1 = RandPhraseSimple("Hayal kurmaya devam et, canlı ele geçirilmeme asla izin vermem!”, “Ancak cesedimi çiğnersin!");
				link.l1.go = "mtraxx_fail";
			}
		break;
		
		case "mtraxx_fail":
            DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddQuestRecord("Roger_3", "27");
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			Mtraxx_PlantPellyClear();
			Mtraxx_TerraxReset(3);
		break;
		// <-- legendary edition
		case "mtraxx_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "İyi bir muhafızımız var, bu yüzden isyan çıkma ihtimali düşük. Ama bir konuda haklısınız: şu alçaklar berbat işçiler. Valinin, don de Losada'ya saygı göstermemi istemesi olmasaydı onları almazdım. Üstelik, onlar için fazla bir şey de istemedi.";
			link.l1 = "Anladım. O halde Los-Teques'e yelken açmam gerekecek... Señor, plantasyonunuzda biraz dolaşıp etrafı keşfetmeme izin verir misiniz? Belki ürünlerinizden satın almak isterim...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Bir tüccar mısınız?";
			link.l1 = "Bazı açılardan, evet. Profesyonel bir tüccar değilim, ama umut vadeden bir anlaşmadan asla vazgeçmem.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "İlginç. Pekâlâ, iznim var. Aklına bir fikir gelirse tekrar gel.";
			link.l1 = "Teşekkür ederim, señor. Sanırım edeceğim.";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   NextDiag.CurrentNode = "plantator_1";
		   pchar.questTemp.Mtraxx = "plant_3";
		   AddQuestRecord("Roger_3", "5");
		   Mtraxx_PlantSetMaxRocur();
		break;
		
		case "mtraxx_5":
            dialog.text = "Neden olmasın? Ne tür mallar sunuyorsun?";
			if (GetSquadronGoods(pchar, GOOD_COFFEE) >= 500)
			{
				link.l1 = "500 kutu kahve.";
				link.l1.go = "mtraxx_coffee";
			}
			if (GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500)
			{
				link.l2 = "500 kutu vanilya.";
				link.l2.go = "mtraxx_cinnamon";
			}
			if (GetSquadronGoods(pchar, GOOD_COPRA) >= 500)
			{
				link.l3 = "500 kutu kopra.";
				link.l3.go = "mtraxx_copra";
			}
		break;
		
		case "mtraxx_coffee":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 11;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "Beş yüz kutu kahve mi? Bakalım... (sayarken) Kahvenizi takas etmeye hazırım, karşılığında "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" şeker çuvalları ve "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  kakao kutuları. Anlaştık mı?";
			link.l1 = "Hmm... Daha iyi şartlar bekliyordum. Neyse, kimin umurunda. Anlaştık!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Güvenilir) Saygıdeğer efendim, itiraz etmeme izin verin! Size en yüksek kalitede mallar getirdim. Hem sunduğumun hem de sizin teklif ettiğinizin her bir biriminin değerini bilirim. Sizin tarafınızdan biraz daha büyük bir payı hak ediyorum ve bu anlaşma sizin için hâlâ kârlı olacak - bunu çok iyi biliyorsunuz.";
				link.l1.go = "mtraxx_PlantVykup_2";
				Notification_Perk(true, "Trustworthy");
			}
		break;
		
		case "mtraxx_cinnamon":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 19;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 106;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 106;
            dialog.text = "Beş yüz kutu vanilya mı? Bak sen... Bakalım... (sayarak) Vanilyanızı takas etmeye hazırım "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" şeker çuvalları ve "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  kakao kutuları. Anlaştık mı?";
			link.l1 = "Hmm... Daha iyi şartlar umuyordum. Neyse, kimin umurunda. Anlaştık!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Güvenilir) Saygıdeğer efendim, itiraz etmeme izin verin! Size en yüksek kalitede mallar getirdim. Hem sunduğumun hem de sizin sunduğunuzun her biriminin değerini bilirim. Sizin tarafınızdan biraz daha büyük bir payı hak ediyorum ve bu anlaşma sizin için hâlâ kârlı olacak - bunu çok iyi biliyorsunuz.";
				link.l1.go = "mtraxx_PlantVykup_2";
				Notification_Perk(true, "Trustworthy");
			}
		break;
		
		case "mtraxx_copra":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 20;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "Beş yüz kasa kopra mı? Bakalım... (sayarak) Kopranızı takas etmeye hazırım "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" şeker çuvalları ve "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  kakao kutusu. Anlaştık mı?";
			link.l1 = "Hmm... Daha iyi şartlar umuyordum... Neyse, kimin umurunda. Anlaştık!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Güvenilir) Saygıdeğer efendim, itiraz etmeme izin verin! Size en yüksek kalitede mallar getirdim. Hem sunduğumun hem de sizin karşılık olarak sunduğunuzun her biriminin değerini bilirim. Sizin tarafınızdan biraz daha büyük bir payı hak ediyorum ve bu anlaşma sizin için hâlâ kârlı olacak - bunu çok iyi biliyorsunuz.";
				link.l1.go = "mtraxx_PlantVykup_2";
				Notification_Perk(true, "Trustworthy");
			}
		break;
		
		case "mtraxx_6":
            dialog.text = "Harika! Bu ikimiz için de kârlı bir anlaşma! Takası ne zaman gerçekleştireceğiz?";
			link.l1 = "Önce malları hazırlamam gerek. Senin de öyle, sanırım. Takası yarın akşam saat dörtte başlatalım. Adamlarım kutuları gün batmadan teslim edecek.";
			link.l1.go = "mtraxx_7";
		break;
		
		
		case "mtraxx_7":
            dialog.text = "Anlaştık. O halde, yarın görüşürüz, señor!";
			link.l1 = "Görüşürüz...";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			AddQuestRecord("Roger_3", "10");
			pchar.questTemp.Mtraxx = "plant_7";
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.mtraxx_plant_goods.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtraxx_plant_goods.win_condition.l1.location = pchar.location;
			pchar.quest.mtraxx_plant_goods.function = "Mtraxx_PlantFindRocurDay";
		break;
		
		case "mtraxx_9":
            dialog.text = "İşte bu kadar, señor. Şeker ya da kakao lazım olursa, lütfen bana uğrayın. Ne zaman isterseniz!";
			link.l1 = "Eğer bu anlaşma kârlı çıkarsa, tekrar görüşürüz. Şimdi gitmeliyim, señor.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_10":
            dialog.text = "Elveda, señor!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantAfterTrading");
		break;
		
		case "mtraxx_soldier_1":
            dialog.text = "Tüccara benzemiyorsun, yabancı. Ruhsatını göster.";
			link.l1 = "Beni bağışlayın! Bir kağıt parçası mı insanların ticaret yapıp yapamayacağına karar veriyor? Bunlar çok pahalı! Daha yeni ticarete başladım ama şimdiden tutkum oldu! Beni bırakın, ikiniz için de sahibine güzel bir söz söyleyeceğim.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_soldier_2":
            dialog.text = "Ağzın çok laf yapıyor, cimri herif. Peki, devam et. Ama patrona seni ona bizim önerdiğimizi söylemeyi unutma.";
			link.l1 = "Elbette. Teşekkür ederim.";
			link.l1.go = "plantation_exit";
		break;
		
		case "mtraxx_PlantVykup_2":
            dialog.text = "Fiyatları iyi biliyorsunuz, Kaptan! Pazarlıkta gerçekten yeteneklisiniz, acemi gibi görünseniz de. Peki, eğer mallarınız gerçekten birinci sınıfsa, size biraz fazladan ödeyeyim bari.";
			link.l1 = "Elbette, birinci sınıf, yemin ederim! Bir şey daha, efendim. Sizden bir şey satın almak istiyorum.";
			link.l1.go = "mtraxx_PlantVykup_3";
		break;
		
		case "mtraxx_PlantVykup_3":
            dialog.text = "Öyle mi? O da neymiş?";
			link.l1 = "Birini, bir şeyi değil. Kölelerinizden birini kişisel hizmetkarım olarak satın almak istiyorum. Bu mümkün mü?";
			link.l1.go = "mtraxx_PlantVykup_4";
		break;
		
		case "mtraxx_PlantVykup_4":
            dialog.text = "Hiç sorun değil. Sana uygun birini buluruz.";
			link.l1 = "Özellikle bir köleyle ilgileniyorum. Şu çekici yüzlü olanla—onu resmi davetlere götürmekten ya da misafirlerine şarap sunarken yanında olmaktan utanmazsın. Adını Jean Picard olarak tanıttı. Şimdiden iyi anlaştık.";
			link.l1.go = "mtraxx_PlantVykup_5";
		break;
		
		case "mtraxx_PlantVykup_5":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 70)
			{
				dialog.text = "Evet, Jean Picard'a talep var – sadece şarap servisi için değil. Nüfuzlu bir İngiliz benimle zaten iletişime geçti. Adı neydi... Pattornson? Bana bir mektup getirdi.";
				link.l1 = "Ama ne Pattornson ne de müşterisi henüz ortada yok. Jean'i hemen şimdi senden satın almaya hazırım. Fiyatını söyle – hanımefendiler bekliyor!";
				link.l1.go = "mtraxx_PlantVykup_10";
				Notification_Skill(true, 70, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Ah, iyi anlaştınız demek. Anlıyorum. Ama üzgünüm, reddetmek zorundayım - Jean Picard satılık değil. Üzgünüm, señor.";
				link.l1 = "Öyle mi? Nedenmiş o? Sana iyi bir ödeme yapmaya hazırım. Sadece fiyatını söyle.";
				link.l1.go = "mtraxx_PlantVykup_6";
				Notification_Skill(false, 70, SKILL_COMMERCE);
			}
		break;
		
		case "mtraxx_PlantVykup_6":
            dialog.text = "Paha biçilemez. Zaten bir alıcısı var. Onu başkasına söz verdim. Söylenecek başka bir şey yok. Başlangıçtaki anlaşmamıza dönelim ve ticareti tamamlayalım.";
			link.l1 = "Hmm, nasıl isterseniz, señor.";
			link.l1.go = "mtraxx_PlantVykup_7";
		break;
		
		case "mtraxx_PlantVykup_7":
            dialog.text = "Harika! Bu ikimiz için de kârlı bir anlaşma! Takası ne zaman gerçekleştireceğiz?";
			link.l1 = "Önce malları hazırlamam gerek. Senin de öyle yapacağına inanıyorum. Takası yarın akşam saat dörtte başlatalım. Adamlarım kutuları gün batmadan önce getirecek.";
			link.l1.go = "mtraxx_PlantVykup_8";
		break;
		
		
		case "mtraxx_PlantVykup_8":
            dialog.text = "Anlaştık. O halde, yarın görüşürüz, señor!";
			link.l1 = "Görüşürüz...";
			link.l1.go = "mtraxx_PlantVykup_9";
		break;
		
		case "mtraxx_PlantVykup_9":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup2 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_1");
		break;
		
		case "mtraxx_PlantVykup_10":
            dialog.text = "Dediğiniz gibi, señor. Ama bilin ki bedeli ağır: beş yüz doblon.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Bu sorun değil - buyurun. İyi bir kişisel hizmetçi, sıradan bir köleden çok daha değerlidir, bunu siz de iyi bilirsiniz.";
				link.l1.go = "mtraxx_PlantVykup_11";
			}
			else
			{
				link.l2 = "Fena bir fiyat biçmişsiniz, efendim. Ama bu köleyle gerçekten ilgileniyorum. Burada bekleyin. Eğer Pattornson gelirse, ona Picard'ın çoktan satıldığını söyleyin - ha-ha-ha!";
				link.l2.go = "mtraxx_PlantVykup_13";
			}
		break;
		
		case "mtraxx_PlantVykup_11":
            dialog.text = "Haklısın. Gerekli düzenlemeleri yapacağım. Picard seni dışarıda bekliyor olacak.";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "mtraxx_PlantVykup_12":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup3 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Maracaibo_ExitTown", "rld", "loc17", "Mtraxx_PlantPlantVykup_2");
		break;
		
		case "mtraxx_PlantVykup_13":
            dialog.text = "Eğer paranın tamamını getirirse, onu geri çevireceğimi sanmam. O yüzden acele et, Kaptan.";
			link.l1 = "Yakında döneceğim.";
			link.l1.go = "mtraxx_PlantVykup_14";
		break;
		
		case "mtraxx_PlantVykup_14":
            DialogExit();
			NextDiag.CurrentNode = "mtraxx_PlantVykup_15";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
		break;
		
		case "mtraxx_PlantVykup_15":
            dialog.text = "Jean Picard için altını getirdin mi, Kaptan? Zaman daralıyor.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Bunun gayet farkındayım. Al altınını, ver bana yeni ev hizmetkârımı.";
				link.l1.go = "mtraxx_PlantVykup_16";
			}
			else
			{
				link.l2 = "Hâlâ topluyorum - bu kadar yüksek bir fiyatı sen belirledin, señor.";
				link.l2.go = "mtraxx_PlantVykup_14";
			}
		break;
		
		case "mtraxx_PlantVykup_16":
            dialog.text = "Bir hizmetli almak için bu kadar harcama yapanı hiç görmemiştim. Ama giyiminize bakılırsa, böyle büyük alışverişlere alışkınsınız. Adamlarıma haber vereceğim, Picard çıkışta sizi bekliyor olacak.";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
	}
} 
