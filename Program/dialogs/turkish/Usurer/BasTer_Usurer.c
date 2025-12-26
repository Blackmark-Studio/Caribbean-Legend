// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Bana bu soruyu kısa bir süre önce de sormuştunuz...","Evet, dur tahmin edeyim... Yine aynı şeyleri mi dönüp duruyorsun?","Bakın, burada mali işleri ben yürütüyorum, sorulara cevap vermem...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye gitti...","Doğru tahmin ettiniz, üzgünüm...","Anladım...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "continue")
            {
                link.l1 = "Ben kaptanım "+GetFullName(pchar)+". Adamınız beni görmek istediğinizi söyledi. Sizi dinliyorum.";
                link.l1.go = "FMQG";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "sucsess")
            {
                link.l1 = "Yine ben, monsieur "+GetFullName(pchar)+". Bertrand Pinette'i getirdim. Şu anda ambarımda.";
                link.l1.go = "FMQG_14";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "letter")
            {
                link.l1 = "Yine ben, monsieur "+GetFullName(pchar)+". Biraz konuşalım.";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers")
            {
                link.l1 = "Yine ben, monsieur "+GetFullName(pchar)+". Biraz konuşalım.";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
            {
                link.l1 = "Yine ben, monsieur "+GetFullName(pchar)+". Sanırım beni tekrar göreceğini beklemiyordun.";
                link.l1.go = "FMQG_23";
            }
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "A-ah, Kaptan "+GetFullName(pchar)+"! Sizi gördüğüme çok sevindim! Sizi bir süredir bekliyordum... Güzel. Size bir soru sormak istiyorum. Bir süre önce, Bertrand Pinette adında bir adam limanda yanınıza gelip geminize binmek istemiş. Zengin görünümlü, lüks bir peruk takıyordu. Size tanıdık geliyor mu?";
			link.l1 = "Evet, öyle. Gerçekten de bana tam olarak bu amaçla yaklaştı.";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			DelLandQuestMark(npchar);
			Log_Info("You have received a heavy purse");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "purse3");
			dialog.text = "Beni ve gemimi mi kiralamak istedi? Kaptan, bu olayın tüm ayrıntılarını bana anlatırsanız bana büyük bir iyilik yapmış olursunuz. Karşılığını fazlasıyla alacaksınız. Alın, içinde altın dolu bir kese. Artık sizin, şimdi lütfen bana Bertrand Pinette hakkında her şeyi anlatın.";
			link.l1 = "Pekâlâ. Bay Pinette, kendisiyle birlikte iki arkadaşını Guadeloupe'tan İspanyol Ana Karası'na götürmem için gemimi kiraladı. Daha doğrusu, Portobello yakınlarındaki Mosquito Körfezi'ne. Görevi tamamladım, gemimden indiler ve doğruca ormana yürüdüler.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "Anlıyorum. Peki, Bay Pinette son varış noktasından bahsetti mi? Ya da yanındaki kişilerden?";
			link.l1 = "Kendi sözlerine göre, Panama'ya gidiyorlarmış. Arkadaşları oldukça ilginçti: biri İspanyol, diğeri Fransız iki subay. Onları bir araya getiren şeyin ne olduğunu hâlâ anlayabilmiş değilim, ama bana soru sormam için para ödenmedi.";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "Bir İspanyol subayı mı? Bir de Fransız subayı mı? Vay canına! Güzel iş, monsieur Pinette! Ne kurnaz adamsın! Burada bile para kazanmanın yolunu bulmuşsun! Panama mı dedin?";
			link.l1 = "Evet, ve bildiğim her şeyi anlattım. Artık gidebilir miyim?";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			dialog.text = "Bekleyin, kaptan. Size bir iş teklifim var. Biraz para kazanmak ister misiniz? Ama önce, yolcularınız hakkında size bir şey anlatayım.";
			link.l1 = "Pekâlâ, dinliyorum.";
			link.l1.go = "FMQG_5";
		break;
		
		case "FMQG_5":
			dialog.text = "Monsieur Bertrand Pinette iki yıl önce kolonimize geldi ve hemen kaptanlarla iş yapmaya başladı. İşleri de, açıkçası, pek temiz değildi... Ona burada büyük kıtlık olan mallar getiriyorlardı—değerli eşyalar, kaçak mallar, bazen de köleler... Yasadışı işlerini finanse etmek için ofisimden düzenli olarak kredi çekti, ama her seferinde faizleriyle birlikte geri ödedi.\nSizden cömertçe yardım aldıktan sonra adadan ayrılmadan önce, her zamankinden çok daha büyük bir kredi çekti. O... güvenilir bir müşteriydi ve kredi geçmişi kusursuzdu, bu yüzden ona kredi verdim. Büyük bir hata. Monsieur Pinette kaçtı ve belli ki paramı geri ödemeye hiç niyeti yok.";
			link.l1 = "Ne kadar büyük bir meblağdan bahsediyoruz, öğrenebilir miyim?";
			link.l1.go = "FMQG_6";
		break;
		
		case "FMQG_6":
			dialog.text = "Bu çok büyük. Yaklaşık yüz elli bin peso değerinde dublon var. On sandık, her birinde yüz elli dublon. Ve bu, faizi bile saymıyorum.";
			link.l1 = "Hm... İki yıldır sana ödeme yapıyordu, seni buna alıştırdı, yüklü bir borç aldı ve sonra ortadan kayboldu. Akıllıca.";
			link.l1.go = "FMQG_7";
		break;
		
		case "FMQG_7":
			dialog.text = "Kesinlikle, kaptan. Bu yüzden sizi bir iş için tutmak istiyorum: o herifi bulup buraya getirin. Vali, komutan ve ben, borcunu sildirecek bir yol buluruz. O adamı gördünüz, yolcunuzdu; yani monsieur Pinette'i bulma şansınız herkesten daha yüksek. Elbette, onun peşine profesyonel ödül avcıları da salacağım, ama sizin yardımınızın daha etkili olacağına dair bir his var içimde.";
			link.l1 = "Bir ödül ne olacak?";
			link.l1.go = "FMQG_8";
		break;
		
		case "FMQG_8":
			dialog.text = "Bu işi yaparsan, sana ağzına kadar altın dolu bir sandık, yüz elli sikke vereceğim.";
			link.l1 = "Bence İspanyol kasabasında yaşayan birini bulup kaçırmak için bu oldukça zavallı bir ödül olurdu.";
			link.l1.go = "FMQG_9";
		break;
		
		case "FMQG_9":
			dialog.text = "Kaptan, Monsieur Pinette'in size benim paramla iyi ödeme yaptığını varsayıyorum, zira teklifimi bu kadar değersiz buluyorsunuz. Size temin ederim, bu çabaya değer. Elbette, reddetme hakkınız var... ama size söyleyeceklerim var ve eminim fikrinizi değiştirecek.";
			link.l1 = "Ve nedir bu?";
			link.l1.go = "FMQG_10";
		break;
		
		case "FMQG_10":
			dialog.text = "Pinette'in Guadeloupe'dan kaçmasından birkaç gün önce, Basse-Terre hapishanesinden bir mahkum firar etti. Adı Don Carlos de Milyar, İspanyol soylusu ve bir subay. Bunu, bir Fransız subayı, Deniz Piyadeleri'nden bir teğmenin ihaneti sayesinde başardı... Ne demek istediğimi anlıyor musun?";
			link.l1 = "Hm... Bu beni neden ilgilendirsin ki? Ben sadece yolcu taşıyordum, hepsi bu.";
			link.l1.go = "FMQG_11";
		break;
		
		case "FMQG_11":
			dialog.text = "Elbette, öyleydiniz! Şahsen, Don de Milyar’ın kaçışını organize etmekle hiçbir alakanız olmadığına hiç şüphem yok. Ama valimiz ve komutanımız böyle düşünmeyebilir. Şanslıysanız suç ortaklığıyla, şanssızsanız... devam etmek istemiyorum. Kendi gözlerinizle görün, kaçak bir İspanyol subayını geminize aldınız, muhtemelen gizli bir koyda... Yanılıyor muyum, kaptan?";
			link.l1 = "Anladım. Bana şantaj yapıyorsun. Buraya gelmekle hata ettim...";
			link.l1.go = "FMQG_12";
		break;
		
		case "FMQG_12":
			dialog.text = "Ne diyorsunuz, kaptan?! Sizi şantajla suçlamıyorum! Tek istediğim, karşılığında iyi bir ödül almak için bana yardım etmeniz. Monsieur Pinette'i bulup onu Basse-Terre'e götürür müsünüz? Dönüşünüzü bekliyor olacağım. Panama'ya gidip dönmek için iki ayın yeterli olacağına inanıyorum.";
			link.l1 = "Bana başka seçenek bırakmıyorsunuz. Yine de, böyle bir ticari yaklaşımın aramızda dostluk kurmaya pek faydası olacağını sanmıyorum. Elveda, monsieur.";
			link.l1.go = "FMQG_13";
		break;
		
		case "FMQG_13":
			DialogExit();
			LocatorReloadEnterDisable("Baster_town", "reload1_back", false);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", false);
			LocatorReloadEnterDisable("Baster_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.FMQG = "headhunter_panama";
			ReOpenQuestHeader("FMQ_Guadeloupe");
			AddQuestRecord("FMQ_Guadeloupe", "7");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 122, false);
			}
			else SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 61, false);
			AddMapQuestMarkCity("panama", false);
			AddLandQuestMark(characterFromId("Panama_tavernkeeper"), "questmarkmain");
			
			// Sinistra - Старт квеста "Мерзкий Божок"
			PChar.quest.ChickenGod_StartLoc.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_StartLoc.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_StartLoc.function = "ChickenGod_BrothelCheck";
		break;
		
		case "FMQG_14":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Harika haber, kaptan! Adamlarımı hemen geminizden bu herifi almaları için göndereceğim. Bu kuş bu sefer elimden kaçamayacak... Ödülünüzü hak ettiniz, alın bu sandığı. Lütfen bana kızmayın, işte size bir muska. Bu, size bir hediye.";
			link.l1 = "Teşekkürler. Sessizliğiniz de ödülümün bir parçası mı?";
			link.l1.go = "FMQG_15";
		break;
		
		case "FMQG_15":
			Log_Info("You have received a chest full of doubloons");
			Log_Info("You have received a 'Fisherman' amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "obereg_7");
			dialog.text = "Sessizlik mi? Neyle ilgili? Sizi müşterilerim arasında görmekten memnuniyet duyarım. Sessizlik ve altın hakkında ne derler bilirsiniz, değil mi?";
			link.l1 = "Bazen altından çok daha değerli olabiliyor, monsieur. Dersimi aldım. Hoşça kalın!";
			link.l1.go = "FMQG_16";
		break;
		
		case "FMQG_16":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			ref sld = characterFromId("FMQG_pass_1");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "23");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		case "FMQG_17":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("baster");
			dialog.text = "Dinliyorum. Bertrand Pinette geminizde, öyle mi?";
			link.l1 = "Hayır. Fakat senin için çok daha iyisi var. Bunu oku.";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_18":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "Bu da ne?";
			link.l1 = "Okumaya devam edin, monsieur. Daha sonra devam edeceğiz.";
			link.l1.go = "FMQG_19";
		break;
		
		case "FMQG_19":
			LAi_Fade("", "");
			dialog.text = "(okuyarak) Hımm ... Ateşli bir hasta hakkında bu saçmalık da ne?";
			link.l1 = "Ciddi misiniz? Peki, bu 'saçmalığı' valiye götüreceğim. 'Courage' gemisinin ve elmas yükünün kayboluşunun ardındaki gerçeği öğrenmeye büyük ilgi göstereceğine inanıyorum... Neden birdenbire benzin attı?";
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter")) link.l1.go = "FMQG_24";
			else link.l1.go = "FMQG_20";
		break;
		
		case "FMQG_20":
			dialog.text = "Demek sonunda Pinette’i buldunuz...";
			link.l1 = "Evet. O halde size bir teklif sunuyorum. Carlos de Milyar'ı, Jean Deno'yu ve diğer saygın beyefendileri unutun, bunu yaparsanız ben de bu mektubu unutacağım.";
			link.l1.go = "FMQG_21";
		break;
		
		case "FMQG_21":
			dialog.text = "Pekâlâ, kaptan... Şartlarınızı kabul ediyorum.";
			link.l1 = "Harika. Umarım bana kızgın değilsinizdir, sanırım işimiz bitti. Hoşça kalın.";
			link.l1.go = "FMQG_22";
		break;
		
		case "FMQG_22":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			pchar.questTemp.FMQG = "cave";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.quest.FMQG_cave.win_condition.l1 = "location";
			pchar.quest.FMQG_cave.win_condition.l1.location = "Guadeloupe_Cave";
			pchar.quest.FMQG_cave.function = "FMQG_InCave";
			// заполним сундук
			pchar.GenQuestBox.Guadeloupe_Cave = true;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse1 = 5;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse2 = 2;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse3 = 1;
			SetFunctionTimerCondition("FMQG_ClearBox", 0, 0, 3, false);
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
			{
				SetFunctionTimerCondition("FMQG_RemoveHunterScore", 0, 0, 1, false);
				AddQuestRecord("FMQ_Guadeloupe", "29");
				DeleteAttribute(pchar, "questTemp.FMQG.Letter");
			}
			else AddQuestRecord("FMQ_Guadeloupe", "25");
		break;
		
		case "FMQG_23":
			dialog.text = "Ha... Haklısınız, kaptan.";
			link.l1 = "Sana verecek bir şeyim var. Bunu al ve oku.";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_24":
			dialog.text = "Demek sonunda Pinette'i buldunuz...";
			link.l1 = "Evet. O halde size bir teklif sunuyorum. Fransız kolonilerinde itibarımı geri kazandırırsanız, bu mektubu unutacağım.";
			link.l1.go = "FMQG_25";
		break;
		
		case "FMQG_25":
			dialog.text = "Ama...";
			link.l1 = "Nasıl yapacağın umurumda değil. Eğer yarına kadar başımdaki av sona ermezse, vali her şeyi öğrenecek.";
			link.l1.go = "FMQG_21";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
