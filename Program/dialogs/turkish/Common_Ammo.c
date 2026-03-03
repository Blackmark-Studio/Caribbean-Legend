// диалог коменданта форта
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
   /*NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}*/
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "First time":
			location = &Locations[FindLocation(pchar.location)];
			if (rand(4) == 4 && GetNpcQuestPastDayParam(location, "gun_date") > 365 && !CheckAttribute(pchar, "questTemp.PrisonGun"))
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Dinle, seninle önemli bir işim var. Umarım bana yardımcı olabilirsin.","Kaptan, size oldukça kârlı bir teklif sunabilir miyim?"),RandPhraseSimple("Bence bize önemli bir konuda yardımcı olabilirsin.","Kaptan, size hem sizin hem de benim için oldukça kârlı olabilecek hassas bir teklifim var."));					
				link.l1 = "Pekala, söyle bakalım derdini, görelim...";
				link.l1.go = "GiveTaskGun";
				location.quest.PrisonGun = "Target"; 
				SaveCurrentNpcQuestDateParam(location, "gun_date");
				break;
			}
		
			dialog.text = RandPhraseSimple("Ben kalenin komutanıyım. Burada ne istiyorsunuz?","Ne istiyorsun? Neden buraya geldin?");
			link.l1 = "Ah, hiçbir şey, sadece kasabayı ve çevresini inceliyorum. Buraya tamamen tesadüfen geldim.";
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "Kale'ye hoş geldiniz, kaptan. Bir şeye ihtiyacınız var mı?";
				link.l1 = "Hayır, hiçbir şey yok, sadece rastgele uğradım.";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Selamlar, Amiral Yardımcısı! Bir emriniz var mı?";
				link.l1 = "Hayır, subayım, hiçbir emir yok. Sadece kaleyi görmeye geldim.";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Genel Vali, Ekselansları! Kale tamamen hazır durumda. Bir emriniz var mı?";
				link.l1 = "İyi olduğuna sevindim, subay. Emir yok, sadece kaleyi kontrol etmeye uğradım.";
			}
			// <-- legendary edition
			link.l1.go = "exit";
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_ammo" && GetQuestPastDayParam("questTemp.Wine_bottle") < 5)
			{
				link.l11 = "Sana ilginç bir bilgi vereceğim, subay. Askerlerinden biri, "+pchar.questTemp.Wine.SName+"   Şehirde şarap almamı benden rica etti, aracılığım sayesinde. Emirlerinizi göz önünde bulundurarak...";
				link.l11.go = "Wine_prison";
			}
			// <-- мини-квест Дефицитный товар
			// Карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "fraht" && NPChar.location == "portpax_ammo")
			{
				link.l11 = "Merhaba, subay. Basse-Terre kolonisinden geliyorum, Gerard LeCroix adında bir adamın emriyle. Ambarımda sizin için barut ve bomba yüklü bir kargo var...";
				link.l11.go = "trial";
			}
			// Опасный груз -->
			if (pchar.location == "Cumana_Ammo")
			{
				if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
				{
					link.l2 = "Endişeli görünüyorsunuz, memur bey. Size nasıl yardımcı olabilirim?";
					link.l2.go = "zpq_prs1";
				}
				if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 15000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
				{
					link.l3 = "Tüm barut yükünün teslim edildiğini bildirmeye hazırım. Gemim boşaltmaya hazır.";
					link.l3.go = "zpq_ex";
				}
				if (pchar.questTemp.zpq == "begin")
				{
					link.l4 = "Barut anlaşmamızı iptal etmek istiyorum. Bu iş fazla zahmetli.";
					link.l4.go = "zpq_fld2";
				}
			}
			// <-- Опасный груз
			NextDiag.TempNode = "First time";
		break;

		// --> Орудия для форта
		case "GiveTaskGun":
			dialog.Text = LinkRandPhrase("Bakın, kalenin topları epeyce eskimiş durumda. Hazine bunları yenilemek için ödenek ayırdı ama açıkçası yeni topları nereden bulacağımı hiç bilmiyorum: bizim kolonimizde gereken miktarda bulmak imkânsız. Bu yüzden, ele geçirdiğiniz gemilerden aldığınız topların burada bizim için çok işe yarayabileceğini düşündüm.","Kaledeki top bataryasını yenilemem gerekiyor. Gerekli ödenek ayrıldı ama, biliyorsunuz... Kolonimizde gereken miktarı satın almak imkânsız.","Kale toplarını yenileriyle değiştirmekle görevlendirildim, ama bir türlü yeterince top bulamıyorum.");
			Link.l1 = "Hmm... Biraz daha ayrıntıya girebilir misin? Kalibre, miktar, fiyat?";
			Link.l1.go = "GiveTaskGun_1";
			pchar.questTemp.PrisonGun = true;
			SaveCurrentQuestDateParam("pchar.questTemp.PrisonGun");
		break;
			
		case "GiveTaskGun_1":
			GetGunType();
			pchar.questTemp.PrisonGun.Sum = makeint(sti(pchar.questTemp.PrisonGun.Price)*sti(pchar.questTemp.PrisonGun.Qty));
			pchar.questTemp.PrisonGun.Luck = rand(4);
			pchar.questTemp.PrisonGun.Id = npchar.location;
			dialog.Text = "İhtiyacım var "+pchar.questTemp.PrisonGun.Text+",   miktarında "+sti(pchar.questTemp.PrisonGun.Qty)+"  tam olarak bu kadar adam. Altın doblonlarla ödeyeceğim, "+sti(pchar.questTemp.PrisonGun.Price)+" parça başına. Toplamda bu kadar tutar "+FindRussianDublonString(sti(pchar.questTemp.PrisonGun.Sum))+" toplamda. Ne dersin? Ha, bir de bir şey daha - tüm partiyi alacağım ama bir ay geçmeden değil, para henüz gelmedi.";
			Link.l1 = RandPhraseSimple("Hayır, memur bey, teklifiniz hiç ilgimi çekmedi... Üzgünüm.","Cazip geliyor, ama sanırım bu sefer pas geçeceğim. Nedenimi kendime saklamama izin verin.");
			Link.l1.go = "exit_gun";
			Link.l2 = RandPhraseSimple("Pekâlâ, bu teklif gerçekten ilginç. Anlaştık sayılır.","Sanırım alacağım. Çok zor değil ve belli ki kârlı.");
			Link.l2.go = "GiveTaskGun_2";
		break;
			
		case "exit_gun":
			dialog.Text = "Büyük talihsizlik kaptan, sana güveniyordum. Ve... umarım bu konuşma kalenin dışına çıkmaz?";
			Link.l1 = "Bunu bana hatırlatmana gerek yok. Saygılar.";
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
			
		case "GiveTaskGun_2":
			dialog.Text = "Pekâlâ, anlaştık! Sana özel bir şart koymuyorum, ama lütfen, işi yarım yıldan fazla uzatma. Ve umarım bunun kesinlikle gizli kalması gerektiğini anlıyorsun?";
			Link.l1 = "Elbette biliyorum. Görüşürüz, Komutan.";
			Link.l1.go = "exit";
			ReOpenQuestHeader("PrisonGun");
			AddQuestRecord("PrisonGun", "1");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			AddQuestUserData("PrisonGun", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("PrisonGun", "sQty", makeint(pchar.questTemp.PrisonGun.Qty));
			AddQuestUserData("PrisonGun", "sSum", makeint(pchar.questTemp.PrisonGun.Sum));
			AddQuestUserData("PrisonGun", "sText", pchar.questTemp.PrisonGun.Text);
			NextDiag.TempNode = "First time";
		break;	
		
		case "CheckGun":
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") < 30)
			{
				dialog.Text = "Sana bir ay geçmeden geri dönmemeni söylemiştim!";
				Link.l1 = "Lanet olsun! O kadar meşguldüm ki"+GetSexPhrase("","")+", kaybettiğim bir "+GetSexPhrase("","")+" zamanın nasıl geçtiğini anlamadım ... Üzgünüm, anlaştığımız gibi sonra tekrar geleceğim.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				break;
			}
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") > 180)
			{
				dialog.Text = "Hmm... Biliyor musun, 'anlaşmamızı' yaptığımızdan beri yarım yıldan fazla zaman geçti. Topları çoktan satın aldım. Gerçekten seni sonsuza kadar bekleyeceğimi mi sandın?";
				Link.l1 = "Lanet olsun! Şimdi onlarla ne yapmam gerekiyor?";
				Link.l1.go = "TakeGun_late";
				break;
			}
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = GetSquadronGoods(Pchar, iGunGoods) - sti(pchar.questTemp.PrisonGun.Qty);
			sTemp = sti(pchar.questTemp.PrisonGun.Qty);
			iTest = FindColony(NPChar.City); // город
			
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.Text = "Evet, bana yardım etmeye hazır mısın?";
				if (amount < 0)
				{
					Link.l1 = "Hayır, hâlâ üzerinde çalışıyorum. Sadece anlaşmamızın hâlâ geçerli olduğundan emin olmak istedim.";
					Link.l1.go = "exit";
				}
				else
				{
					Link.l1 = "Benim. Tüm parti ambarın içinde - "+sTemp+" birimler, anlaştığımız gibi.";
					Link.l1.go = "TakeGun";
				}
			}
			else 
			{
				dialog.text = "Limanımızda gemini göremiyorum. Topları ormandan sürükleyerek mi götüreceğiz diyorsun? Limanımıza çabuk git ve geri dön.";
				link.l1 = "Gemiğim adanın öbür tarafında. Onu limana getireceğim.";
				link.l1.go = "exit";
			}
		break;
		
		case "TakeGun":
			if (pchar.questTemp.PrisonGun.Luck == 4)
			{
				dialog.Text = RandPhraseSimple("Biliyor musun, bu gerçekten garip ama anlaşmamızdan çekilmek zorundayım. Az önce mali bir denetim geçirdik ve bu konularda ne kadar titiz olduklarını bilirsin. Elimden hiçbir şey gelmiyor. Üzgünüm.","Kaptan, biliyorsunuz... Şey, toplar metropolden bize gönderildi ve tabii ki onları almak zorunda kaldım. Fahiş fiyatlar ama... Sizi hayal kırıklığına uğrattığım için gerçekten üzgünüm... Ben de bundan hiç memnun değilim.");
				Link.l1 = "Kahretsin! Şimdi onlarla ne yapmam gerekiyor?";
				Link.l1.go = "TakeGun_no";
			}
			else
			{
				dialog.Text = RandPhraseSimple("Mükemmel. Onları boşaltmak için garnizondan bir ekip göndereceğim.","Mükemmel. Askerlerim topları boşaltmana yardım edecek.");
				Link.l1 = "Ödemeyi hazırladın mı?";
				Link.l1.go = "TakeGun_1";
			}
		break;
		
		case "TakeGun_no":
			dialog.Text = " Bilmiyorum. Tersanede sat, bir ticaret gemisi donat, batır... Gerçekten hiçbir fikrim yok. Ve lütfen, bu anlaşmadan kimseye bahsetme.";
			Link.l1 = "Yok artık! Gerçekten ne diyeceğimi bilemiyorum!";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "3");
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_late":
			dialog.Text = "Hiçbir fikrim yok. Bu senin sorunun. Sat, at, batır – gerçekten umurumda değil.";
			Link.l1 = "Ah, bu tam bir zaman kaybıydı...";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "4");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_1":
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = sti(pchar.questTemp.PrisonGun.Qty);
			iTemp = sti(pchar.questTemp.PrisonGun.Sum);
			dialog.Text = "Elbette. İşte altının - istediğin gibi kullan.";
			Link.l1 = "Teşekkür ederim! Sizinle iş yapmak gerçekten keyifliydi!";
            Link.l1.go = "TakeGun_2";
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("You have received "+FindRussianDublonString(sti(pchar.questTemp.WPU.Escort.Money))+"");
			PlaySound("interface\important_item.wav");
			RemoveCharacterGoods(Pchar, iGunGoods, amount);
		break;
		
		case "TakeGun_2":
			dialog.Text = "Bu his karşılıklı. Çok yardımcı oldun. Ve lütfen, bu anlaşma bu odada kalsın, sana yalvarıyorum.";
			Link.l1 = "Elbette. Size en iyi dileklerimi sunarım.";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "2");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		// <-- орудия для форта

		//Jason --> мини-квест Дефицитный товар
		case "Wine_prison":
			dialog.text = "Ne?! Kalede içki içmeyi kesinlikle yasaklamıştım! Bunun bedelini ödeyecek. Ödemesinden 1000 peso keseceğim ve seni dikkatli davrandığın için ödüllendireceğim. Ayrıca bu adam üç gün hücrede kalacak.";
			link.l1 = "Teşekkür ederim, "+GetAddress_FormToNPC(NPChar)+". Böyle ihlalleri durdurmak hepimizin ortak görevi.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 1000);
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			pchar.quest.Wine_Exchange.over = "yes";//снять прерывание
			pchar.quest.WineTraderQM.over = "yes";//снять прерывание
			WineTraderQMDel();
			sld = characterFromId(pchar.questTemp.Wine.id);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			NextDiag.TempNode = "First time";
		break;
		// <-- мини-квест Дефицитный товар
		
		// Карибские нравы
		case "trial":
			iTest = FindColony(NPChar.City); // город
			QuestPointerDelLoc("portpax_town", "reload", "gate_back");
			QuestPointerDelLoc("portpax_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("portpax_fort", "reload", "reload2");
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetSquadronGoods(pchar, GOOD_BOMBS) < 2500 || GetSquadronGoods(pchar, GOOD_POWDER) < 2500)
				{
					dialog.text = "Hmm. Ama bu parti tam dolu değil! Bu nasıl oldu?";
					link.l1 = "Lanet olsun! Lütfen beni affedin, bu benim hatam. Hemen eksik olan miktarı satın alıp, anlaştığımız gibi tüm partiyi size teslim edeceğim.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Demek bizim kuryemiz sensin? Peki. Önce yükle ilgili işleri halledelim, sonra sana daha fazla talimat verilecek.";
					link.l1 = "Pekala.";
					link.l1.go = "trial_1";
				}
			}
			else
			{
				dialog.text = "Limanımızda gemini göremiyorum. Yükü ormanın içinden mi taşıyalım diyorsun? Limanımıza aceleyle git ve geri dön.";
				link.l1 = "Gemim adanın öbür tarafında. Onu limana getireceğim.";
				link.l1.go = "exit";
			}
		break;
		
		case "trial_1":
			if(!bImCasual) pchar.quest.Trial_FrahtFail.over = "yes"; // belamour legendary edition если был - снять таймер
			dialog.text = "Pekala, bombalar ve barut, her birinden 2.500 birim... Güzel. Askerler yükü boşaltacak, adamların biraz dinlenebilir. İşte taşıma ücreti - beş bin peso.";
			link.l1 = "Teşekkürler! Şimdi ne yapmalıyım? Monsieur LeCroix şöyle dedi...";
			link.l1.go = "trial_2";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_2":
			AddMoneyToCharacter(pchar, 5000);
			RemoveCharacterGoods(pchar, GOOD_BOMBS, 2500);
			RemoveCharacterGoods(pchar, GOOD_POWDER, 2500);
			dialog.text = "Evet, evet, şimdi talimatlarını alacaksın. Dikkatini vermeye hazır mısın?";
			link.l1 = "Tabii, memur bey.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "So, our military ship 'Warlike' is cruising near the Spanish colony Porto Bello, in the southern part of the Spanish Main. This vessel is under the command of Florian Shoke, who is preparing an ambush of a Spanish heavy galleon set to leave Porto Bello in two weeks.\nThe problem is that our frigate's cannons are suffering from a casting defect, and we need to replace fifteen cannons to save the mission; otherwise, the galleon will outnumber 'Warlike' in both guns and men. \nWithout the replacement, Florian Shoke will be forced to sail away with no result. Such a sequence of events is highly undesirable. Your task is to save the mission by delivering fifteen cannons within fourteen days.";
			link.l1 = "Yani, on beş topu gemiye alıp Portobello'ya gitmem, 'Militant' firkateynini bulup topları Kaptan Florian Shoke'a teslim etmem gerekiyor?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "Aynen öyle. Doğru anladın. Bu görevi üstlenmeye hazır mısın?";
			link.l1 = "Ödeme ne olacak?";
			link.l1.go = "trial_5";
			link.l2 = "Üzgünüm, memur bey, ama bu işe karışmak istemiyorum. Lütfen beni mazur görün.";
			link.l2.go = "trial_exit";
		break;
		
		case "trial_exit":
			dialog.text = "Haklısınız, ama sizinle anlaşacağımı ummuştum. Şimdi başka bir kurye bulmam gerekecek, ama fazla vaktim kalmadı... Neyse, sizi daha fazla tutmayayım, kaptan.";
			link.l1 = "Saygılarımla.";
			link.l1.go = "trial_exit_1";
		break;
		
		case "trial_exit_1":
			DialogExit();
			AddQuestRecord("Trial", "6");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "trial_5":
			dialog.text = "Bunun için endişelenme. Florian Shoke sana geminin hazinesinden iki yüz altın doblon ödeyecek. Ayrıca, eminim ki seni ve gemini kendi amaçları için kullanmak isteyecektir - tabii ki senin rızanla.";
			link.l1 = "Pekala, bu görevdeyim! Toplar nerede?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "Hemen askerlerime onları geminize yüklemelerini emredeceğim. En kısa sürede yelken açın, monsieur! Bol şans!";
			link.l1 = "Teşekkürler. Şans da, rüzgarın arkadan esmesi de fena olmaz...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			DialogExit();
			AddQuestRecord("Trial", "7");
			pchar.questTemp.Trial = "cannon";
			// belamour legendary edition
			if(!bImCasual) SetFunctionTimerCondition("Trial_CannonFail", 0, 0, 21, false); 
			else NewGameTip("Exploration mode: timer is disabled.");
			SetCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24)+15);
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				EnemyNationHunterOnMap(true);//запуск перехватчиков
			}
			pchar.quest.Trial_cannon.win_condition.l1 = "location";
			pchar.quest.Trial_cannon.win_condition.l1.location = "Portobello";
			pchar.quest.Trial_cannon.function = "Trial_CreateFlorianFrigate";
			// Sinistra - квест "Встреча с Диего"
			bDisableFastReload = true;
			PChar.quest.VsD_GiumDyubua.win_condition.l1 = "location";
			PChar.quest.VsD_GiumDyubua.win_condition.l1.location = "PortPax_Fort";
			PChar.quest.VsD_GiumDyubua.win_condition = "VsD_GiumDyubua";
			AddMapQuestMarkShore("Shore47", false);
		break;
		
		// Опасный груз -->
		case "zpq_prs1":
			if(!isBadReputation(pchar, 70))
			{
				dialog.text = "Hm, belki de. Şey, iyi itibarın sayesinde sana güvenmeyi deneyeceğim. Yoksa bunu seninle konuşmazdım bile. Mesele şu ki, oldukça büyük bir özel yük partisine ihtiyacımız var, bu yüzden büyük bir gemiye ve risk almaya istekli olman gerekiyor. Ayrıca, kimseye bundan bahsetmeyeceğine dair bana söz vermelisin.\nEğer bu seni rahatsız ediyorsa, hemen şimdi söyle. Sanırım kendimi yeterince açık ifade ettim...";
				link.l1 = "İlginç geliyor. Ödeme adil olursa varım, ama hangi yükten bahsettiğini hiç bilmiyorum. Yine de, sözüm söz.";
				link.l1.go = "zpq_prs2";
				link.l2 = "Bence hayır derim, sanırım... Sana söz versem, çalışmam gerekecek, bu da epey zahmetli görünüyor. Yapmam.";
				link.l2.go = "zpq_fld";
				Notification_Reputation(true, 71, "low");
			}
			else
			{
				dialog.text = "Senin itibarın benim için kabul edilemez. Lütfen odadan çıkmanı istiyorum. Sorunlarımızı kendimiz çözebiliriz.";
				link.l1 = "Ne yaparsan yap, o zaman onları çöz...";
				link.l1.go = "exit";
				Notification_Reputation(false, 71, "low");
			}		
		break;
		
		case "zpq_fld":
			dialog.text = "Pekâlâ, en azından bana dürüstçe reddettin... Seni daha fazla tutmayacağım.";
			link.l1 = "Elveda.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "failed";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_fld2":
			dialog.text = "Hm, aslında bunu senden beklemezdim. Senden gitmeni istemek zorundayım... Ve unutma, hiçbir bilgiyi ifşa etmeyeceğine dair verdiğin sözü hatırla.";
			link.l1 = "Üzgünüm...";
			link.l1.go = "exit";
    		ChangeCharacterComplexReputation(pchar,"nobility", -3);
			if (pchar.questTemp.zpq == "begin")
			{
				AddQuestRecord("zpq", "6");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
			}
			pchar.questTemp.zpq = "failed";
		break;
		
		case "zpq_prs2":
			dialog.text = "Harika. Harika. Sorun şu ki, son fırtına kalenin cephaneliğindeki barut stoklarımıza zarar verdi. Buradaki sıkıntının ne kadar hassas olduğunu sana açıklamama gerek yoktur umarım. Uzun bir kuşatma olursa kale hiçbir şey yapamaz. Çok fazla dayanamayız.";
			link.l1 = "Şimdi anladım. Ne tür bir yük istiyorsun – ve ne kadar?";
			link.l1.go = "zpq_prs3";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_prs3":
			dialog.text = "15.000 varil baruta ihtiyacımız var. Sana 100.000 peso ödeyeceğim... Anlamalısın ki bu gerçekten iyi bir fiyat. Şu anki durumumuz beni böyle bir masrafı kabul etmeye zorluyor, valinin veznedarını ikna etmek de kolay olmadı... Fırtına mevsimi kendi tedarik hatlarımızı kullanmamıza izin vermiyor ve bu sorunu herkesin bilmesini de istemiyoruz...";
			link.l1 = "Anladım... fiyat gerçekten iyi. Risklerden bahsetmiştiniz...";
			link.l1.go = "zpq_prs4";
		break;
		
		case "zpq_prs4":
			dialog.text = "I meant that such a large amount of gunpowder can be very dangerous during transportation. I have seen a few explosions with my own eyes; sometimes a single spark is enough. But if you face a storm... Whole convoys usually keep their distance from a potential brander. If it explodes, then everyone is dead!";
			link.l1 = "Anladım... Ama ben her zaman sözümü tutarım, oldu bilin.";
			link.l1.go = "zpq_prs5";
			link.l2 = "Pekâlâ, señor... Bana öyle korkunç şeyler anlattınız ki, o işi yapma isteğim tamamen kayboldu.";
			link.l2.go = "zpq_fld2";
		break;
		
		case "zpq_prs5":
			dialog.text = "Güzel, bir anlaşmaya vardığımıza çok memnunum. Yükü bana getirdiğinde sana ödemeni yapacağım.\nParayı bir hafta içinde hazır edeceğim, daha önce değil, o yüzden acele etmene gerek yok, ama yine de çok geciktirmemeni rica ederim.";
			link.l1 = "Anladım, señor. Hemen ilgileniyorum.";
			link.l1.go = "zpq_prs5_ok";
		break;
		
		case "zpq_prs5_ok":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.zpq = "begin";
			pchar.questTemp.zpq.time = 20;
			AddQuestRecord("zpq", "1");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			SaveCurrentQuestDateParam("pchar.questTemp.zpq");
		break;
		
		case "zpq_ex":
			dialog.text = "Sonunda! Anlaşmamızı unuttuğunu düşünmeye başlamıştım. Askerlerim hemen gemini boşaltmaya başlasın. Barut işi çok hassastır, ha-ha!";
			link.l1 = "Harika, señor, ama ödemeyi hatırlatmam gerekiyor.";
			link.l1.go = "zpq_ex2";
			RemoveCharacterGoods(pchar, GOOD_POWDER, 15000);
			AddCharacterExpToSkill(pchar, "Sailing", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 500);

            pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
            pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
            pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
		break;
		
		case "zpq_ex2":
			dialog.text = "Evet, tabii ki. Anlaştığımız gibi 50.000 peso alacaksınız.";
			link.l1 = "Muhtemelen benimle dalga geçiyorsun, señor?! 100.000 peso için anlaşmıştık!";
			link.l1.go = "zpq_ex3";
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "(Güvenilir) Beni kandırmaya kalkacağından şüphelenmeye başladım, bu yüzden 125.000 pesosumu almadan buradan ayrılmam!";
				link.l2.go = "zpq_ex4";
			}
			link.l3 = "Hm... Görüyorum ki şartlar değişmiş. Eh, en iyisi parayı alıp gitmek...";
			link.l3.go = "zpq_ex5";
		break;
		
		case "zpq_ex3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 35)
			{
				Notification_Skill(true, 36, SKILL_LEADERSHIP);
				dialog.text = "Ah, evet... Tam olarak! 100.000 peso. Unutmuşum, affedin beni. Yaşlılık işte, skleroz malum... Elbette, işte paralarınız. Sizinle iş yapmak bir zevkti, kaptan. Şimdi, üzgünüm ama yapmam gereken çok iş var...";
				link.l1 = "Sana da aynısı, señor. Görüşürüz.";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
				AddQuestRecord("zpq", "2");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 100000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				Notification_Skill(false, 36, SKILL_LEADERSHIP);
				dialog.text = "Ne?! Al paranı ve defol, yoksa bu zindanda çürürsün!";
				link.l1 = "Sen böyle bir yalancısın ki, señor! Sana tavsiyem, paramı isteyerek geri ver, yoksa yüküne el koyarım!";
				link.l1.go = "zpq_ex_agry";
				link.l2 = "Affedersiniz... Peki, teklif ettiğiniz meblağı kabul ediyorum ve işimiz burada bitti.";
				link.l2.go = "zpq_ex5";
			}
		break;
		
		case "zpq_ex4":
				dialog.text = "Böyle bir kabalık olmaz! Akıl hastası değilim ve 100.000 peso teklif ettiğimi gayet iyi hatırlıyorum.\n Kahretsin! Oyunlarına alet olmayacağım!";
				link.l1 = "Sakin ol. Kalenin tam önünde barutla dolu bir yangın gemisi olduğunu düşün. Eğer tek bir kelime edersem, kalen yerle bir olur.";
				link.l1.go = "zpq_ex6";
		break;
		
		case "zpq_ex6":
			dialog.text = "Hm-Hm... sağlam bir gerekçe. 125.000 peso, diyorsun? Al, buyur, ve şimdi beni affet, yapacak işlerim var...";
			link.l1 = "Elveda, señor. Görüşürüz.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "5");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 125000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			/*else
			{
				dialog.text = "Ne?! Ben bir subayım! Beni korkutabileceğini mi sanıyorsun, çocuk?! Muhafızlar, alın "+GetSexPhrase("onu","onu")+"!";
				link.l1 = "Deneyin de görelim, mahzen fareleri...";
				link.l1.go = "zpq_ex_war";
			}*/
		break;
		
		case "zpq_ex5":
			dialog.text = "Harika! Doğru seçimi yaptınız. Alın paralarınızı ve hoşça kalın. Tanıştığımıza memnun oldum!";
			link.l1 = "Elveda...";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "3");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 50000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		break;
		
		case "zpq_ex_agry":
			dialog.text = "Ah, kahpe herif! Muhafızlar, yakalayın "+GetSexPhrase("onu","onun")+"!";
			link.l1 = "Vay canına! Görünen o ki, paramı senin cansız bedeninden almam gerekecek...";
			link.l1.go = "zpq_ex_war";
		break;
		
        case "zpq_ex_war":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			pchar.questTemp.zpq = "failed";
            AddQuestRecord("zpq", "4");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 100000;
			AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum)*2 + rand(5000)));
			GiveItem2Character(npchar, "blade_21");
			EquipCharacterbyItem(npchar, "blade_21");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			npchar.cirassId = Items_FindItemIdx("cirass3");
			chrDisableReloadToLocation = true;
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_group_SetCheck(slai_group, "OpenTheDoors");
			AddSimpleRumour("Such terrible things happen here! They say that some prisoner has escaped from the casemates! He slaughtered all the guards, stole the treasury, and just went away! Shiver me timbers!", SPAIN, 5, 1);
		break;
		// <-- Опасный груз
	}
}

void GetGunType()
{
	int iGunType;
	if(makeint(pchar.rank) < 6) iGunType = rand(1);	//18&&24
	if(makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 15) iGunType = rand(2); //24&&32	
	if(makeint(pchar.rank) >= 15 && makeint(pchar.rank) < 24) iGunType = rand(2)+2; //32&&36&&42
	if(makeint(pchar.rank) >= 24) iGunType = 5-rand(1); //36clv&&42
	int iAdd = makeint(GetSummonSkillFromName(pchar, SKILL_COMMERCE)/20);
	
	switch (iGunType)
	{
		case 0:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_24;     					
			pchar.questTemp.PrisonGun.Price = 28 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "24 calibre cannons";
		break; 
		case 1:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_18;     					
			pchar.questTemp.PrisonGun.Price = 25 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "couleuvrines";
		break; 
		case 2:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_32;     					
			pchar.questTemp.PrisonGun.Price = 32 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "32 calibre cannons";
		break; 
		case 3:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_36;     					
			pchar.questTemp.PrisonGun.Price = 36 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "36 calibre cannons";
		break;
		case 4:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_36;     					
			pchar.questTemp.PrisonGun.Price = 49 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "full couleuvrines";
		break; 
		case 5:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_42;     					
			pchar.questTemp.PrisonGun.Price = 40 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+20+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "42 calibre cannons";
		break; 
	}
}
