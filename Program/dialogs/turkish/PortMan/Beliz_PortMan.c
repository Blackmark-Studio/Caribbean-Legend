// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//регата
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "Ne istiyorsun? Ah, sen regattaya katılanlardan birisin! Doğru mu?";
				link.l1 = "Aynen öyle, efendim. Kurallara göre burada kaydımı yaptırmam gerekiyor.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular?","Ne istiyorsun, "+GetAddress_Form(NPChar)+"?"),"Bana zaten bir soru sormaya çalıştınız "+GetAddress_Form(NPChar)+"...","Bugün üçüncü kez aynı soruyu sordunuz...","Bak, eğer limanın işleriyle ilgili bana söyleyecek bir şeyin yoksa, sorularınla beni meşgul etme.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim.","Konuşacak bir şeyim yok."),"Boşver.","Gerçekten de, üçüncü kez oldu artık...","Üzgünüm, ama şimdilik liman işleriyle ilgilenmiyorum.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Грани справедливости
			if (CheckAttribute(pchar, "questTemp.GS_Portman"))
			{
				link.l1 = "Birinin hayatına kastettiği, senin de suçluyu bulmaya çalıştığın söyleniyor?";
				link.l1.go = "GS_Portman_1";
			}
			if (CheckAttribute(pchar, "questTemp.GS_NaemnikMertv"))
			{
				link.l1 = "Sizin hayatınıza kasteden adam öldü, Bay "+npchar.lastname+". Artık seni hiçbir şey tehdit etmiyor.";
				link.l1.go = "GS_Portman_6";
			}
			//<-- Грани справедливости
		break;

		//регата
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
			dialog.text = "Hm... Regatta kurallarını çiğnediniz ve sizi diskalifiye etmek zorundayım. Üzgünüm. Bir sonraki yolculuğa katılamayacaksınız. Port Royal'a gönderilecek raporu zaten hazırladım.";
			link.l1 = "Ah... ne yazık! Ama burada yapabileceğim bir şey yok, çok dikkatliydin. Hoşça kal!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.FirstTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1 переход
			dialog.text = "Kayıt olalım: Kaptan "+GetFullName(pchar)+", gemi şu anda "+pchar.Ship.Name+"...   regatta'nın süresi saat olarak  "+sti(pchar.questTemp.Regata.FirstTransitionTime)+". Tamam, sonucun kaydedildi, yoluna devam edebilirsin.";
			link.l1 = "Rütbemi söyle.";
			link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "Buradasınız ama geminizi göremiyorum. Nerede?";
			link.l1 = "Üzgünüm efendim. Gemimi hemen limana çekeceğim.";
			link.l1.go = "exit";
		}
		break;
		
		case "Regata_info":
			int n=1;
			string sTemp, sName, sShip;
			for (int i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				if (pchar.questTemp.Regata.AdversaryFirstTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FirstTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "Önde gidiyorsun. Tebrikler! Böyle devam et!";
			link.l1 = "Teşekkürler!";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "4");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Sen sonuncusun. Acele etmelisin.";
				link.l1 = "Yoldayım!";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "9");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "Sen ikincisin. Lider ise "+sName+" gemide "+sShip+". Sanırım hâlâ ondan kaçabilirsin.";
					link.l1 = "Teşekkürler! Deneyeceğim!";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "5");
					}
					else
					{
					dialog.text = "Rütbeniz "+n+". En yakın rakibiniz "+sName+" gemide "+sShip+".";
					link.l1 = "Teşekkürler!";
					link.l1.go = "exit";
					if (n==3) AddQuestRecord("Regata", "6");
					if (n==4) AddQuestRecord("Regata", "7");
					if (n==5) AddQuestRecord("Regata", "8");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Beliz = "true";//отметка Белиза
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Hispaniola2";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 3
			pchar.questTemp.Regata.AttackIsland = "Cuba1";
			pchar.questTemp.Regata.AttackNation = SPAIN;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";//первая засада у Сантьяго
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Гаваны
			pchar.questTemp.Regata.Town = "Portpax";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Portpax_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
		break;
		//регата
		
		//--> Грани справедливости
		case "GS_Portman_1":
			dialog.text = "Hayatıma gerçekten bir suikast girişimi oldu, bu doğru. Ama arama meselesi... tam olarak öyle değil. Bir kaçak yakalanmasını istemiyorum — onun kafasını istiyorum. Ancak o zaman huzura kavuşabilirim.";
			Link.l1 = "Sana kim saldırdı ve nedenini biliyor musun?";
			Link.l1.go = "GS_Portman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_2":
			dialog.text = "Ben... Ben onun kim olduğunu bilmiyorum! Nereden geldiğini ya da neden bana saldırdığını da bilmiyorum. Ama bir şey açık — beni öldürmek istedi. Ve şimdi... şimdi ben de onun ölümünü aynı öfkeyle istiyorum! Anlıyor musun?\nO yüzden bana boş sorular sormayı bırak. Merakın bana hiçbir şey ifade etmiyor — artık sadece harekete geçmek işe yarar. Kellesi için iki yüz dublon, fiyatım bu. Avı başlat ya da vaktimi boşa harcama.";
			Link.l1 = "Korku ve öfkenin zihnini bulandırdığını anlıyorum, hatta üslubunu bile affedeceğim. Ama kendine hakim ol. Sorunlarını çözmek için sıraya giren gönüllüler görmüyorum, o yüzden öfkeni dizginle. İki yüz doblon kabul edilebilir, ama işi almadan önce her şeyi bilmem gerek.";
			Link.l1.go = "GS_Portman_3";
			Link.l2 = "Sözlerin sadece boş laf, ortada hiçbir ipucu yok. Ormanda bilinmeyen birini aramak samanlıkta iğne aramaya benzer. Zamanımı böyle anlamsız bir avda harcamam. Bol şans. Buna gerçekten ihtiyacın olacak.";
			Link.l2.go = "GS_Portman_End";
		break;
		
		case "GS_Portman_End":
			DialogExit();
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
		break;
		
		case "GS_Portman_3":
			dialog.text = "Ah... Beni affedin, "+GetAddress_Form(NPChar)+", sinirlerim yıprandı... Tam olarak ne bilmek istiyorsun?";
			Link.l1 = "Onu tanımlamama yardımcı olabilecek herhangi bir özelliğini fark ettiniz mi? Yalnız mıydı, yoksa arkasında daha güçlü biri mi vardı? Ne kadar çok anlatırsanız, o kadar çabuk huzur içinde uyuyabilirsiniz.";
			Link.l1.go = "GS_Portman_4";
		break;
		
		case "GS_Portman_4":
			dialog.text = "Ne düşmanı?! Hiç düşmanım yok! Hiç olmadı! Gündüz vakti, sokağın ortasında öldürülmeyi hak edecek hiçbir şey yapmadım\nO alçak... sadece öfkeli bir deli, bu sömürge kasabalarında her yerde rastlanan cinsten\nNerede arayacağınıza gelince... Sanırım ormanda saklanıyor. O lanetli ağaçların arasında kaybolmak kolay, ama eminim mağaralara ya da koylara gidecek — saklanmak orada daha kolay\nGörünüşüne gelince, yüzü bir atkıyla kapalıydı, başında bir şapka vardı ve Majestelerinin muhafızlarından bile fazla silah taşıyordu. Başka bir şey fark edecek zaman yoktu.";
			Link.l1 = "Pek fazla değil ama aramaya başlamak için yeterli. Hemen yola çıkıyorum. O altını yanında tut — yakında döneceğim.";
			Link.l1.go = "GS_Portman_5";
		break;
		
		case "GS_Portman_5":
			DialogExit();
			AddDialogExitQuestFunction("GS_Portman_5");
		break;
		
		case "GS_Portman_6":
			dialog.text = "Harika, "+GetFullName(pchar)+"   Muhteşem! Eşsiz yeteneğinizi kanıtladınız. İşte ödülünüz – iki yüz doblon. Lütfen, buyurun alın! ";
			Link.l1 = "Sana teşekkür ederim! Ama söyle bana, katilin eski müşterilerinden biri tarafından tutulduğundan şüphelenmek için bir nedenin var mı?";
			Link.l1.go = "GS_Portman_7";
			AddItems(pchar, "gold_dublon", 200);
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_7":
			dialog.text = "Eski müşteriler mi?.. Ne saçmalık!... Ben dürüst bir adamım, işlerim her zaman şeffaf olmuştur! Ama bana yardım ettiğin için bir şey paylaşacağım. Kısa bir süre önce korsanlar bana geldi.\nTüccar gemileriyle ilgili bilgi karşılığında para teklif ettiler. Reddettim, tehditler ve lanetler savurup öyle çıktılar. Suikastçının onların işi olduğuna inanıyorum. Hayır cevabını kolay kolay kabul etmezler.";
			Link.l1 = "Öyleyse, kendine dikkat et. Kim bilir, bu 'korsanlar' daha kaç paralı adam gönderecek? Şimdi gitmem gerek — görev beni bekliyor.";
			Link.l1.go = "GS_Portman_8";
		break;
		
		case "GS_Portman_8":
			dialog.text = "Bekleyin, Kaptan. Size bir kez daha teşekkür etmek istiyorum. Altından da öte, benim takdirimi kazandınız. Ben burada Liman Şefi olduğum sürece, gemilerinizden herhangi birini burada istediğiniz kadar süreyle yüzde elli indirimle demirleyebilirsiniz. Nasıl buldunuz?";
			Link.l1 = "Çok cömert bir teklif! Bir kez daha teşekkür ederim!";
			Link.l1.go = "GS_Portman_9";
		break;
		
		case "GS_Portman_9":
			dialog.text = "Ve çabalarınız için bir kez daha teşekkür ederim. Eminim ki, önemli olana odaklandığınız sürece işleriniz bugün olduğu gibi yolunda gitmeye devam edecek. Hoşça kalın, Kaptan.";
			Link.l1 = "Hoşça kal.";
			Link.l1.go = "GS_Portman_10";
		break;
		
		case "GS_Portman_10":
			DialogExit();
			AddDialogExitQuestFunction("GS_Portman_10");
		break;
		//<-- Грани справедливости
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
