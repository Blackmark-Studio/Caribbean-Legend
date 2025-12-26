// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Bana bu soruyu kısa bir süre önce sormuştun...","Evet, dur tahmin edeyim... Yine aynı şeyleri mi dönüp dolaşıyorsun?","Bakın, burada finans işlerini ben yürütüyorum, sorulara cevap vermem...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Doğru tahmin ettiniz, üzgünüm...","Anlıyorum...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Şu küpelere bir bakın, monsieur. Onları ormanda bir haydutun cebinde buldum. Bunlar kesinlikle usta bir kuyumcunun işi ve eminim ki bu vahşi topraklardan gelmiyor. Ne dersiniz?";
                link.l1.go = "Sharlie_junglejew";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
			{
				link.l1 = "Folke Deluc adında bir borçlunuz olduğunu biliyorum. Söyleyin, onun gecikmesi ne kadar ciddi?";
                link.l1.go = "Sharlie";
			}	
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
			{
				link.l1 = "Folke Deluc'un borcu hakkında buradayım.";
                link.l1.go = "Sharlie_repeat";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
			{
				link.l1 = "Verdiğiniz görevi tamamladım, monsieur. İşte sizin... İspanyol dostunuz.";
                link.l1.go = "Sharlie_14";
			}
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik"))
			{
				link.l1 = "Buraya ... hakkında geldim.";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat"))
			{
				dialog.text = "40 doblon getirdin mi?";
				if (PCharDublonsTotal() >= 40)
				{
					link.l1 = "Subayım için olan paranız burada...";
					link.l1.go = "Del_Deluck_5";
				}
				link.l2 = "Hayır, hâlâ düşünüyorum.";
				link.l2.go = "exit";
			}
			//<-- Миниквест "Делюк"
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "Ve neden bununla ilgileniyorsunuz, sorabilir miyim?";
			link.l1 = "Bu adamın serbest kalmasını istiyorum, parmaklıklar ardında değil. Bildiğim kadarıyla, bu borç size ödenmeden serbest bırakılmayacak. Bu borcu ödemekle ilgileniyorum.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Aha, bu her şeyi değiştirir. Ben de paramı geri almakla ilgileniyorum... Bu Folke Deluc tuhaf bir adam. Oldukça küçük bir miktar - beş bin peso - ödünç aldı. Geri ödemeyi reddetti ve saklanmaya başladı. Sonunda faiz, asıl borca yetişti ve kendini parmaklıklar ardında buldu.";
			link.l1 = "Öyleyse şu anda borcu on bin olmuş mu?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Tam olarak on bin dört yüz elli peso, monsieur. Yani özgürlüğünün bedeli bu kadar. Bunu bana ödemeye razı mısınız? Biraz şaşırdım...";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Şaşırma. İşte para.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "Hm... Gerçekten de yüklü bir meblağ. Bakın, monsieur, belki siz ve ben bir anlaşmaya varabiliriz? Mesela, sizin için halledebileceğim bir iş olabilir, siz de bana olan minnettarlığınızı bu on bin beş yüz olarak değerlendirebilirsiniz...";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart")) link.l2.go = "Sharlie_5x";
			else link.l2.go = "Sharlie_5"; // Addon 2016-1 Jason пиратскаЯ линейка 1
		break;
		
		case "Sharlie_3":
			AddMoneyToCharacter(pchar, -10450);
			dialog.text = "Evet, bu denizciye gerçekten ihtiyacınız olduğu belli, çünkü onun için bu kadar para ödemeye razı olmuşsunuz. Neyse, bu benim işim değil, değil mi, monsieur? İşte borç senedi, artık onun borcunu talep etme hakkınız var. Ve tabii ki, hapisten salıverilmesi için bir dilekçe.";
			link.l1 = "Tam olarak istediğim buydu. Hoşça kal, "+npchar.name+"!";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			Log_Info("You have received a bill of debt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Sharlie = "freeskiper";
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
		break;
		
		case "Sharlie_5x": // Addon 2016-1 Jason пиратскаЯ линейка 1
			dialog.text = "Bir iyilik mi? Ne yazık ki, senden hiçbir iyiliğe ihtiyacım yok. En azından şimdilik.";
			link.l1 = "Yazık. O zaman parayı Folke'ye götürmeliyim. Hoşça kal!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_5":
			dialog.text = "Bir iyilik mi? Hm... Biliyor musunuz, efendim, dün gelseydiniz size olumsuz yanıt verirdim, ama şimdi... evet, halledilmesi gereken bir işim var, fakat uyarıyorum, oldukça tehlikeli.";
			link.l1 = "Ne için tehlikeli?";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "Elbette, değerli hayatınız için. Bu yüzden kabul etmeden önce iyice düşünün ve böyle bir şeyi yapmaya gerçekten istekli olup olmadığınıza karar verin.";
			link.l1 = "Monsieur, tehlike bana yabancı değil. Daha önce defalarca tehlikeli durumlarda bulundum. O yüzden, ayrıntılara geçelim. Eğer bütün kalenin garnizonunu tek başıma ortadan kaldırmam gerekmiyorsa, belki de bu kadar gizemli şekilde ima ettiğiniz şeyi başarabilirim.";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			dialog.text = "Pekala. O zaman dinle. Bu gece, birkaç korsan ve bir mahkum, Le Francois'daki korsan ininden çıkıp Le Marin koyuna yürüyecekler. Mahkum bir İspanyol subayı ve tahkimat mühendisliğinde büyük bir uzman. İngilizler onu kendi amaçları için kullanmak istiyorlar, bu yüzden adamı koydan almak üzere bir savaş gemisi gönderecekler.\nSubay benim eski dostum ve onun İngilizlerin eline esir düşmesini istemiyorum. Yerel yetkililerden yardım isteyemem çünkü İspanya ile savaş halindeyiz. Daha fazla vaktim olsaydı, İspanyol'u... pardon, dostumu geri alabilecek adamlar tutardım, ama ne yazık ki!\nBu işi güvenebileceğim tek kişi sensin. Le Marin koyuna gitmeli ve... korsanları mahkumu sana vermeye ikna etmelisin. Pek işbirliği göstereceklerini sanmıyorum, o yüzden gerisi sana kalmış.";
			link.l1 = "Konvoyda kaç korsan olacak?";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			dialog.text = "Bilmiyorum. Belki iki kişi, belki üç ya da dört. Peki, sen ne dersin?";
			link.l1 = "Sana zaten 'tehlike bana yabancı değil' dediğimi ve kılıcın hangi ucundan tutulacağını bildiğimi söylemiştim.";
			link.l1.go = "Sharlie_10";
			link.l2 = "Hm. Haklısın, bu tehlikeli. Bir grup korsana tek başıma saldırmam.";
			link.l2.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "Bu senin kararın. Eğer bu işi yapamayacağına inanıyorsan, en iyisi hemen reddet. O zaman Deluc'un borç parasını bekliyor olacağım.";
			link.l1 = "Pekala. Parayı ona getireceğim. Sonra görüşürüz!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_10":
			dialog.text = "Pekâlâ. Bunu duyduğuma sevindim. O halde Le Marin koyuna gitmelisin, korsanlar orada akşam yediden sabah dörde kadar olacaklar. Sakın kaçırma! Ve sakın gemi kullanmayı düşünme! Böyle bir hareket onları korkutur, oraya ormandan yürüyerek git!\nMahkûmu bulduğunda bana getir, kapıyı açık tutacağım. Şehre dönmeden önce saat bir olmasını beklemeni tavsiye ederim, çünkü muhafızların dikkatini çekmemelisin. Dikkatli ol ve bol şans!";
			link.l1 = "Teşekkür ederim! Gerçekten biraz şansa ihtiyacım olacak...";
			if (CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE)) link.l1.go = "Sharlie_13";
			else link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Bir dakika! Bakıyorum ki silahın bile yok. Benimkilerden birini al. Yanında birkaç mermisi de var. İşine yarayacağını düşünüyorum.";
			link.l1 = "Evet, bu kesinlikle işime yarayacak. Teşekkür ederim, monsieur.";
			link.l1.go = "Sharlie_12";
		break;
		
		case "Sharlie_12":
			Log_Info("You have received a combat pistol");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol1");
			TakeNItems(pchar, "bullet", 20);
			TakeNItems(pchar, "gunpowder", 20);
			dialog.text = "Ve şimdi git, Tanrı yardımcın olsun!";
			link.l1 = "...";
			link.l1.go = "Sharlie_13";
		break;
		
		case "Sharlie_13":
			DialogExit();
			pchar.quest.Sharlie_captive_Tut.win_condition.l1 = "location";
			pchar.quest.Sharlie_captive_Tut.win_condition.l1.location = "Shore39";
			pchar.quest.Sharlie_captive_Tut.function = "Tutorial_Rest_Delay";
			pchar.quest.Sharlie_captive.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_captive.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_captive.function = "Captive_Timer";
			SetFunctionTimerCondition("Captive_CreatePiratesOver", 0, 0, 1, false);
			AddQuestRecord("SharlieD", "1");
			pchar.questTemp.Sharlie = "bankskiperfight";
			pchar.questTemp.Sharlie.Captive = "true";
			pchar.questTemp.Sharlie.Captive.Name = GetFullName(npchar);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload2_back");
		break;
		
		case "Sharlie_14":
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";
			pchar.quest.Sharlie_captive3.over = "yes";
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("shore39", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload8_back");
			DelLandQuestMark(npchar);
			ref sld = characterFromId("CaptiveSpain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 5.0);
			sld.lifeday = 0;
			SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			dialog.text = "Harika! Bu işi başarıyla halledebildiğine çok memnun oldum. Operasyonun ayrıntılarını bilmem gerekmiyor, değil mi?  Demek ki, sevgili İspanyol misafirim artık evimde kendini güvende hissedebilir...";
			link.l1 = "Folke Deluc'un borcu ne olacak?";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Of course, yes. Take his bill of debt; now you're entitled to his debt and have the right to ask for money from him. Well, and of course, petition for his release from prison. Have I done everything as promised?";
			link.l1 = "Evet, monsieur. Her şey anlaşmaya tamamen uygun. Şimdi müsaadenizle ayrılıyorum.";
			link.l1.go = "Sharlie_4";
			AddQuestRecord("SharlieD", "7");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
		break;
		
		case "Sharlie_repeat":
			dialog.text = "Yani, borcunu ödemeye hazır mısınız?";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Evet. İşte para.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "Ne yazık ki, hâlâ gereken miktarı toplayamadım...";
			link.l2.go = "exit";
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Hm. Görünüşe bakılırsa haklısınız, bunlar gerçekten pahalı küpeler ve kesinlikle Eski Dünya'da yapılmış... Ne diyebilirim ki? Size otuz... hayır, hatta otuz beş altın dublon veririm. Parayı alın, daha iyi bir fiyat bulamazsınız.";
			link.l1 = "Otuz beş dublon mu? Fena bir fiyat değil. Kabul ediyorum. Alın bakalım.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "Hayır. Sanırım bu küpeleri kendime saklayacağım.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the earrings");
			RemoveItems(pchar, "jewelry25", 1);
			TakeNItems(pchar, "gold_dublon", 35);
			AddQuestRecord("SharlieE", "3");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		//--> Миниквест "Делюк"
		case "Del_Deluck":
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			dialog.text = "Biliyorum, biliyorum Kaptan. Seyirciniz neredeyse her Fransız kolonisinde borç biriktirmiş gibi görünüyor. Doğrusunu söylemek gerekirse, bunu uzun zamandır biliyorum. Meslektaşlarımla görüştüm, standart bir prosedürdür bu...";
			link.l1 = "Ve önceki anlaşmamız sırasında beni bilgilendirmenin yeterince önemli olduğunu düşünmediniz mi?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "Neden? O zamanlar önceliğim Deluc'un bana olan borcuydu, ki bu arada en büyük borç da oydu. Siz onu ödedikten sonra, derhal meslektaşlarıma haber verdim... Geniş bir profesyonel kurye ağımız var, bu yüzden kısa sürede masamda Deluc'un senetlerinden bir yığın birikti.";
			link.l1 = "Anlıyorum... Onları, o adamla yakından ilgilendiğimi ve ödeme gücüm olduğunu bilerek satın aldınız... Bu düpedüz şantaj, Monsenyör.";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "Bu sadece işim, Kaptan! Seyircinizin bugüne kadar olan toplam borcu 40 dublon tutuyor ve unutmayın, faiz işlemeye devam ediyor... Ödeyecek misiniz?";
			link.l1 = "Henüz cevap vermeye hazır değilim, ama düşüneceğim. Hoşça kal!";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik_repeat = true;
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.dialog.currentnode = "Del_Deluck";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Mükemmel! Ne yapman gerektiğini biliyorsun – tıpkı geçen seferki gibi. İşte belgeler – bunları hapishane komutanına sun. Seninle iş yapmak büyük bir zevkti, Kaptan.";
			link.l1 = "Bu durumda keyif alınacak pek bir şey yok. Hoşça kal.";
			link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(40);
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			Log_Info("You have received a bill of debt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Del_DeluckSvoboda = true;
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
