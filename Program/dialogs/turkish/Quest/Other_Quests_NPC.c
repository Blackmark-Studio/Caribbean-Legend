void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
        
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- работорговец -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//--> пинас
		case "TakeShoreCap":
    		dialog.text = "Alçak! Seni şaşırttım, değil mi!";
    		link.l1 = "Ne?";
    		link.l1.go = "Node_1";
		break;
		
		case "Node_1":
			dialog.text = "Ha-ha! Burada köle yok! Onlar için geldin, değil mi?";
			link.l1 = "Kahretsin. Ticaret pinasında neden bu kadar çok asker olduğunu merak ediyordum... Tuzakmış!";
			link.l1.go = "Node_2";
		break;
		
 		case "Node_2":
			dialog.text = "Evet, alçak, bu bir tuzak. Ben bir tüccar değilim, askeri bir subayım! Dövüşü kazanmış olabilirsin ama adaletten kaçamayacaksın!";
			link.l1 = "Ve nedenmiş o? Şimdi işini bitireceğim, gemini batıracağım ve kimsenin ruhu duymayacak.";
			link.l1.go = "Node_3";
		break;
		
 		case "Node_3":
			dialog.text = "Yanılıyorsun. O bankerle yaptığın işler ortaya çıktı. Yakında genel vali senin küçük planından haberdar olacak ve darağacından kaçamayacaksın. Ama sana bir iyilik yapıp seni burada ve şimdi öldüreceğim!";
			link.l1 = "Denesene bak, valinin köpeği!";
			link.l1.go = "Node_4";
		break;
		
 		case "Node_4":
 		    pchar.questTemp.Slavetrader = "TakeShoreCap_end"; //это состояние квеста для проверки у квестодателя
            AddQuestRecord("Slavetrader", "13");
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
            pchar.quest.Slavetrader_DieHard.over = "yes";
			pchar.quest.Slavetrader_AfterBattle.over = "yes";
			pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
            Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
		    LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Slave_arest":
			dialog.text = ""+GetFullName(pchar)+", kanun adına, tutuklusun! Silahlarını teslim et ve bizimle gel!";
			link.l1 = "Ne oluyor, memur bey? Teslim mi olayım? Hangi gerekçeyle?";
			link.l1.go = "Slave_arest_1";
		break;
		
		case "Slave_arest_1":
			dialog.text = "Aptal numarası yapma, kaptan! Kirli işlerin ortaya çıktı. İşlediğin katliam ve o gemi için "+NationNameGenitive(sti(npchar.nation))+" batırdığın için seni asacaklar, göreceksin!";
			link.l1 = "Pekâlâ, madem öyle diyorsun... Git kendi işine bak!";
			link.l1.go = "Slave_arest_2";
		break;
		
		case "Slave_arest_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> крыса в доме
		case "Rat_bandos":
			dialog.text = "Hey, burada ne yapıyorsun?!";
    		link.l1 = "Neden bu kadar kabasınız, iyi beyefendi? Şu fare Gontier burada bir yerde mi saklanıyor, ha?";
    		link.l1.go = "Node_rat_1";
		break;
			
		case "Node_rat_1":
			dialog.text = "Hayır, değil! Dışarı çık!";
			link.l1 = "Görünüşe göre yalan söylüyorsun. Evi arayacağım ve göreceğiz...";
			link.l1.go = "Node_rat_2";
		break;
		
 		case "Node_rat_2":
			dialog.text = "Siktir git! François! Kaç! Arkadaşlar, yardım edin!";
			link.l1 = "Lanet olsun!";
			link.l1.go = "Node_rat_3";
		break;
		
		case "Node_rat_3":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat1");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Rat_lover":
			dialog.text = "Ah! Lütfen, bana zarar verme!";
    		link.l1 = "Ne...? Francois Gontier nerede? Söyle bana, pis kadın, yoksa sen de arkadaşların gibi olacaksın!";
    		link.l1.go = "Rat_lover_1";
		break;
			
		case "Rat_lover_1":
			dialog.text = "Hayır, hayır, her şeyi anlatacağım! Pencereden atladı ve gemisine doğru koştu.";
    		link.l1 = "Hangi gemi? Limanda ona ait bir gemi olmadığını biliyorum. Bana yalan söyleme kızım, yoksa işler daha da kötüleşir...";
    		link.l1.go = "Rat_lover_2";
		break;
			
		case "Rat_lover_2":
			dialog.text = "Yalan söylemiyorum, yemin ederim! Küçük bir adaya indiğini ve buraya bir sandalla geldiğini söyledi... Kesin oradadır! Lütfen bana zarar verme!";
    		link.l1 = "Pekala, doğruyu söylüyor gibisin. Burada kal ve sessiz ol. Bir dahaki sefere arkadaş edinmenin daha akıllıca bir yolunu bulmaya çalış. Ama biliyor musun, gözlerinden anlıyorum, bana aklının pek çalışmadığını söylüyorlar.";
    		link.l1.go = "Rat_lover_3";
			pchar.quest.Slavetrader_RatAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_RatAttack.win_condition.l1.location = "Tortuga";//отправляем в локацию
            pchar.quest.Slavetrader_RatAttack.function = "Slavetrader_RatCorvette";//создание корвета
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Slavetrader_RatCorvetteOver", 0, 0, 1, false);
		break;
			
		case "Rat_lover_3":
 		    LAi_SetPlayerType(pchar);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Slavetrader", "21_9");
            DialogExit();
		break;
		
		//--> беглые рабы
		case "Slave_woman":
			dialog.text = "Bizi bağışlayın! Merhamet edin! Teslim oluyoruz!";
    		link.l1 = "Öyle mi? Hemen ambar bölümüne git! Aptallık yapmaya kalkan olursa vururum!";
    		link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_Slavewoman");
		break;
	//<--работорговец
			
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- Генераторы -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//--> Jason ------------------------ Сомнительное предложение -------------------------------------------	
		int iCGood;
		case "Contraoffer_patrol":
			chrDisableReloadToLocation = false;
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.PatrolSumm = sti(pchar.GenQuest.Contraoffer.Trader.Summ)/3;
			dialog.text = "Pekâlâ, pekâlâ... Burada ne varmış bakalım? Kolonimizde izinsiz kişilerle ya da aralarında mal ticareti yapmanın yasak olduğunu bilmiyor musun?";
			link.l1 = "Öyle mi, memur bey? Açıkçası, bunu ilk kez duyuyorum. Bu kararname yakın zamanda çıkarıldı, değil mi?";
			link.l1.go = "Contraoffer_patrol_1";
			link.l2 = "Ne, ticaret mi "+GetGoodsNameAlt(iCGood)+"? Hiçbir şey göremiyorum "+GetGoodsNameAlt(iCGood)+" etrafında, memur. Ben sadece bu parlak paraları görüyorum... O da aynısını görüyor. Neden sen ve askerlerin de bizim paralarımıza bir bakmıyorsunuz?";
			link.l2.go = "Contraoffer_patrol_pay1";
		break;
		
		case "Contraoffer_patrol_1":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > hrand(120))
			{
				dialog.text = "Bilmiyordun, öyle mi? Hmm... yalan söylemiyorsun gibi görünüyor. Ama yine de kanunu çiğnedin. Seni tutuklamayacağım, fakat bir ceza ödemen gerekiyor. Ve yük meselesine gelince... anlaşmanın diğer tarafıyla ayrıca konuşacağız.";
				link.l1 = "Ve o ceza ne kadar?";
				link.l1.go = "Contraoffer_patrol_pay2";
			}
			else
			{
				dialog.text = "Aptal numarası yapma, kaptan! Herkes bunu çoktan biliyor, söylemiş olayım. İkinizi de kaçakçılıktan tutukluyorum ve yükünüze el konulacak.";
				link.l1 = "Kasematları sevmem, subay. Açık denizi tercih ederim... ve şimdi oraya yelken açacağım. Ama anlaşılan bunu ancak senin cesedinin üzerinden yapabileceğim.";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "Teslim olmaktan başka çarem yok. Ama gerçekten hiçbir fikrim yoktu!";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_pay1":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) > hrand(120))
			{
				dialog.text = "Şimdi konuşuyorsun... Hadi bakalım, paralarını görelim... Sanırım oldukça belirli bir miktar duydum - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+" . Şimdi üç katılımcımız olduğuna göre, ben de "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm))+". Bu senden, aynısı arkadaşından da.";
				link.l1 = "Elbette, memur bey. İşte parlak paralarım, ya da daha doğrusu, sizin parlak paralarınız – az önce sahilde yanlışlıkla düşürdünüz... Ve başka bir şey yok "+GetGoodsNameAlt(iCGood)+" işte burada, ha-ha, sana söylemiştim.";
				link.l1.go = "Contraoffer_patrol_complete1";
				link.l2 = "Vay canına! Çok açgözlüsün, subay. Annen sana açgözlülüğün iyi bir şey olmadığını öğretmedi mi? Sanırım seninle kılıcımla hesaplaşmak bana daha ucuza patlayacak.";
				link.l2.go = "Contraoffer_patrol_fight";
			}
			else
			{
				dialog.text = "Şaka mı yapıyorsun, kaptan? Bana rüşvet mi teklif edeceksin? Tutuklusun! Yakalayın onu!";
				link.l1 = "Pekâlâ, paramı görmek istemiyorsan, kılıcıma bak o zaman!";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "Teslim olmaktan başka çarem yok. Ama gerçekten hiçbir fikrim yoktu!";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_complete1":
			dialog.text = "Evet, galiba haklısınız... Burada birkaç beyefendi ve parlak paralarım dışında ilginç bir şey yok. Gidebilirsiniz kaptan, biz de ortağınızla biraz konuşacağız.";
			link.l1 = "Görüşürüz, memur. Ona zarar verme.";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_pay2":
			dialog.text = ""+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm))+" . İyi ruh halime teşekkür et.";
			link.l1 = "Teşekkür ederim, memur bey. Gerçekten hiçbir fikrim yoktu... Buyurun, cezamı ödemeye hazırım.";
			link.l1.go = "Contraoffer_patrol_complete2";
			link.l2 = "Anladığım kadarıyla siz de pek dürüst değilsiniz, memur. Cezanız fazla yüksek. Sanırım bu koloniyi sizin varlığınızdan kurtararak yardımcı olacağım.";
			link.l2.go = "Contraoffer_patrol_fight";
		break;
		
		case "Contraoffer_patrol_complete2":
			dialog.text = "Pekâlâ. Artık gidebilirsin. Sana tavsiyem, bir daha böyle durumlara düşmemek için yerel yasaları öğrenmen. Şimdi git, biz bu ticaretin ikinci tarafıyla ilgileneceğiz, her şeyden haberi vardı, orası kesin.";
			link.l1 = "Peki, o halde size iyi günler, memur bey.";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_complete":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm));
			AddQuestRecord("Contraoffer", "6");
			CloseQuestHeader("Contraoffer");
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "Contraoffer_patrol_fight":
			AddQuestRecord("Contraoffer", "7");
			CloseQuestHeader("Contraoffer");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -5);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Contraoffer_patrol_jail":
			dialog.text = "Komutan seninle ilgilenecek. Beni takip et!";
			link.l1 = "...";
			link.l1.go = "Contraoffer_patrol_jail_exit";
		break;
		
		case "Contraoffer_patrol_jail_exit":
			GoToPrison(pchar.GenQuest.Contraoffer.Trader.City, sti(pchar.GenQuest.Contraoffer.Trader.Summ), 7);
			DialogExit();
			AddQuestRecord("Contraoffer", "8");
			CloseQuestHeader("Contraoffer");
			pchar.GenQuest.Contraoffer.Jail = "true";
		break;
	//<-- Сомнительное предложение	
		
	//Jason --> ----------------------------------- Неудачливый вор --------------------------------------------
		case "Device_poorman":
			dialog.text = "Günaydın. Bir şeye ihtiyacınız var mı?";
			link.l1 = "Evet, dostum. Demek sen benim adamımsın. Çalan sendin "+pchar.GenQuest.Device.Shipyarder.Type+"  yerel tersaneden mi? Her şey seni işaret ediyor, o yüzden tartışmaya gerek yok.";
			link.l1.go = "Device_poorman_1";
		break;
		
		case "Device_poorman_1":
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance3))
			{
				case 0://выбросил
				if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) != 1)
				{
					dialog.text = "Sana yalvarıyorum, efendim! Evet, bu tuhaf şeyi tersaneden çaldım. Ama satmayı başaramadım, kimse böyle bir şeyi istemiyor. O yüzden de ondan kurtuldum. Bağışlayın beni, iyi kalpli beyim, açlığımı suçlayın, beni değil... Yoksa asla hırsızlık yapmaya cesaret edemezdim!";
					link.l1 = "Bu bir sorun... Ve sana da ihtiyacım yok. Benim bulmam gereken o "+pchar.GenQuest.Device.Shipyarder.Type+". Söyle bana, onu nereye attın?";
					link.l1.go = "Device_poorman_0_1";
				}
				else //просто отдаст
				{
					dialog.text = "Sana yalvarıyorum, efendim! Evet, bu garip şeyi tersaneden çaldım. Ama satmayı başaramadım, kimse böyle bir şeyi istemiyor. Onu sana vereceğim. Al, lütfen bana zarar verme ve askerlere haber verme!";
					link.l1 = "Pekâlâ, yaşayabilirsin, serseri. Derine ihtiyacım yok, bana o alet lazım. Hemen ver onu ve defol!";
					link.l1.go = "Device_poorman_0_2";
				}
				break;
				case 1://упирается, хитрый или храбрый
					dialog.text = "Ne demek istiyorsun?  Ne "+pchar.GenQuest.Device.Shipyarder.Type+"? Anlamadım!";
					link.l1 = "Bunu sana ya da cesedine aradığımda alacağım! Şimdi ver onu bana!";
					link.l1.go = "Device_poorman_1_1";
				break;
				case 2://трусливый
					dialog.text = "Ah... Bu da ne "+pchar.GenQuest.Device.Shipyarder.Type+"? Ben... peki bu da ne?";
					link.l1 = "Aptal numarası yapmaya ya da kaçmaya çalışma, seni nasıl olsa yakalarım. Sadece ceplerini kontrol etmeme izin ver...";
					link.l1.go = "Device_poorman_2_1";
				break;
			}
		break;
		
		case "Device_poorman_0_1"://идем на поиски
			dialog.text = "Şehir kapılarının hemen arkasında, ormanın çok uzağında değil. Ne olur, iyi beyefendi! Eğer o şeye gerçekten ihtiyacınız varsa, kendiniz alabilirsiniz. Hâlâ orada olmalı, eminim.";
			link.l1 = "Seni bunu bulmaya ve bana getirmeye zorlamalıyım, ama seni bulmak için harcayacağım zamanın, onu bulmaktan daha fazla olacağından korkuyorum "+pchar.GenQuest.Device.Shipyarder.Type+". Bunu kendim yapacağım. Ama bana yalan söylüyorsan seni bulurum!";
			link.l1.go = "exit";
			AddQuestRecord("Device", "3");
			string sCity = pchar.GenQuest.Device.Shipyarder.City + "_ExitTown";
			ref rItm = ItemsFromID("Tool");
			rItm.shown = true;
			rItm.startLocation = sCity;
			rItm.startLocator = "item" + (rand(14)+1);
			Log_TestInfo("Device is at the locator " + rItm.startLocator);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_0_2"://получили девайс
			dialog.text = "Al, bunu al. Teşekkür ederim, iyi kalpli beyefendi!";
			link.l1 = "Eh, aradığım şey bu olmalı... ha! Artık gidebilirsin. Yürü. Bir dahaki sefere daha dikkatli ol.";
			link.l1.go = "exit";
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "4");
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_1":
			pchar.GenQuest.Device.Shipyarder.Poorsumm = 1000+hrand(1000);
			dialog.text = "Dinle, bu çalgıdan mı bahsediyorsun? O bana ait ve ben onu çalmadım! Ayrıca sana bedavaya vermeye de niyetim yok. Eğer istiyorsan, bana parasını öde "+FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))+".";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))
			{
				link.l1 = "Hm... Peki. Sana parasını ödeyeceğim. Al şu paraları, şimdi de bana enstrümanı ver!";
				link.l1.go = "Device_poorman_1_2";
			}
			link.l2 = "Gerçekten mi? Sence sana güveneceğimi mi sandın, sefil hırsız? Ver bakalım "+pchar.GenQuest.Device.Shipyarder.Type+" şimdi bana yoksa muhafızları çağırırım, birlikte tersaneye gider ve bu aletin gerçekten kime ait olduğuna karar veririz.";
			link.l2.go = "Device_poorman_1_3";
			link.l3 = "Sen aptal mısın, yoksa ne? Dinle, hergele, iki seçeneğin var: ya bana verirsin "+pchar.GenQuest.Device.Shipyarder.Type+" ya da seni bıçaklarım ve o aleti cesedinden alırım!";
			link.l3.go = "Device_poorman_1_4";
		break;
		
		case "Device_poorman_1_2":
			dialog.text = "Güzel anlaşma, kaptan! Sanırım hepimiz kârımızdan payımızı alacağız, he-he... al bakalım.";
			link.l1 = "Daha az konuş, hırsız! Beni kandırdığını sanma, sadece bu işi huzur içinde ve daha az sorunla halletmek istiyorum. Bu paralar sana hiçbir fayda sağlamaz zaten. Defol git!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Device.Shipyarder.Poorsumm));
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "5");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm)));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_3":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "Hayır! Muhafızları çağırma! Ben... bu lanet aleti sana vereceğim. Al, işte!";
				link.l1 = "Şimdi çok daha iyi! Defol git! Yoksa kendini darağacında bulursun, bu sadece an meselesi.";
				link.l1.go = "exit_device";
			}
			else//храбрый попался
			{
				dialog.text = "Ne gardı, kaptan? Burada sadece sen ve ben varız. Fazla tartışıyorsun, o yüzden seni sakinleştirmem gerekecek... kılıcımla.";
				link.l1 = "Bana tehditler savurmaya cüret mi ediyorsun, pislik?!";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_1_4":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "Ah! Yardım edin! Katil!";
				link.l1 = "Olduğun yerde kal, köpek!";
			link.l1.go = "exit";
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				AddQuestRecord("Device", "7");
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else//храбрый попался
			{
				dialog.text = "Pekâlâ, bakalım kim kimi hançerleyecek, kaptan!";
				link.l1 = "Bana tehdit mi savuruyorsun, pislik?!";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_2_1":
			dialog.text = "Birini mi arıyorsunuz? Lütfen, efendim!";
			link.l1 = "Şimdi dinle, ya tersaneden az önce çaldıklarını güzelce teslim edersin, ya da seni komutanın ofisine götürürüm. Sonunda yine bana vereceksin, ama önce topukların kızgın demirle dağlanacak. Belki de ardından asarlar seni. Seçim senin.";
			link.l1.go = "Device_poorman_2_2";
			link.l2 = "Çaldıklarını derhal ver, alçak, yoksa seni olduğun yerde gebertirim!";
			link.l2.go = "Device_poorman_2_3";
		break;
		
		case "Device_poorman_2_2":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 2)//тут уж как повезёт
			{
				dialog.text = "Önce beni yakalaman gerekecek, eğer beni komutanın ofisine götürmek istiyorsan ...";
				link.l1 = "Olduğun yerde kal, köpek!";
				link.l1.go = "exit";
				AddQuestRecord("Device", "7");
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else
			{
				dialog.text = "Hayır, beni komutanın ofisine götürme! Onu sana kendim vereceğim! Al, işte bu, bunu arıyor olmalısın. Zaten kimse satın almazdı...";
				link.l1 = "Eh, seni kaleye götürebilirim sanırım... Peki, ver aleti ve yoluna git!";
				link.l1.go = "exit_device";
			}
		break;
		
		case "Device_poorman_2_3"://напугали
			dialog.text = "Ah! Lütfen bana zarar verme, ne varsa al! Al, hepsi senin olsun!";
			link.l1 = "İşte şimdi konuşuyorsun! Kaybol, eğer seni bu kasabada bir daha görürsem komutana teslim ederim. Elveda!";
			link.l1.go = "exit_device";
		break;
		
		case "exit_device":
			npchar.lifeday = 0;
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "6");
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_fight":
			chrDisableReloadToLocation = true;
			sld = characterFromId("Device_poorman");
			TakeNItems(sld, "Tool", 1);
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
            sld.DontClearDead = true; // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Device", "8");
			AddComplexSelfExpToScill(30, 30, 30, 50);
		break;
	//<-- Неудачливый вор
//-------------------------------------------почтовый генератор 2 уровня------------------------------------	
		case "PostGopHunters":
			dialog.text = "Dur orada, dostum! Taşıdığın bir şeye ihtiyacımız var. Onu ver, sonra yoluna devam edebilirsin.";
			link.l1 = "Ne hakkında konuşuyorsun?";
			link.l1.go = "PostGopHunters_1";
			link.l2 = "Bu sokak serserileri bu aralar fazla küstahlaştı... Hazırlanın, alçaklar!";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_1":
			dialog.text = "Aptal numarası yapma! Paketi bize ver, yaşarsın. Yoksa... cesedinden alırız!";
			link.l1 = "Şans sizden yana... alın bakalım, alçaklar, başka çarem yok.";
			link.l1.go = "PostGopHunters_2";
			link.l2 = "Pekâlâ, deneyebilirsin!";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_2":
			dialog.text = "Diline dikkat et, dostum... Şansını zorlamaman akıllıca olmuş. Sonu yine aynı olurdu, ha-ha! Bir süre daha yaşayacaksın... Görüşürüz.";
			link.l1 = "...";
			link.l1.go = "exit_gophunter";
		break;
		
		case "PostProfHunters":
			dialog.text = "Bekle, "+GetAddress_Form(NPChar)+", böyle aceleyle gitme. Sana verecek bir işim var.";
			link.l1 = "Hangi iş? Seni tanımıyorum.";
			link.l1.go = "PostProfHunters_1";
		break;
		
		case "PostProfHunters_1":
			dialog.text = "Seni tanıyorum, kaptan. Şimdi, doğrudan konuya gelelim. Az önce aldın "+pchar.questTemp.WPU.Current.Add+" in "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+". Bunu inkâr etmeye çalışma, bunu kesin olarak biliyoruz - sonuçta, bu belgeyi birkaç gündür arıyoruz.";
			link.l1 = "Şimdi anladım. Ee, ne olmuş?";
			link.l1.go = "PostProfHunters_2";
		break;
		
		case "PostProfHunters_2":
			dialog.text = "Paketimi ver, böylece kısa buluşmamız sona ersin. Kahramanlık yapmaya kalkma kaptan, bu belgeleri alacağız ve gerekirse şehir muhafızlarıyla savaşmaya hazırız\nAnlayacağın üzere, bir çatışma çıkarsa önce sen ölürsün. O yüzden belgeleri ver, dostça yollarımızı ayıralım.";
			link.l1 = "Şans sizden yana... alın, alçaklar, başka çarem yok.";
			link.l1.go = "PostProfHunters_3";
			link.l2 = "Beni mi korkutmaya çalışıyorsun? Senin yapabileceğinden daha fazlasını küçük balıklar bile gösterdi! Defol.";
			link.l2.go = "PostProfHunters_4";
		break;
		
		case "PostProfHunters_3":
			dialog.text = "Makul davrandığınız için memnunum, kaptan. Bu işi kabul ederek kendinizi büyük bir tehlikeye attınız. Şimdi izninizle ayrılıyorum, eğer sakıncası yoksa.";
			link.l1 = "...";
			link.l1.go = "exit_profhunter";
		break;
		
		case "PostProfHunters_4":
			dialog.text = "Bu senin kararındı...";
			link.l1 = "...";
			link.l1.go = "PostHunters_fight";
			TraderHunterOnMap(false);//если деремся - запускаем ДУ вдогонку
		break;
		
		case "PostHunters_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_gophunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "11");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "exit_profhunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "12");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			pchar.questTemp.WPU.Postcureer.fail = "true";
			DialogExit();
		break;
		
		case "PostAgent":
			bDisableFastReload = true; 
			dialog.text = "Bekle, "+GetAddress_Form(NPChar)+", acele etme böyle. Sana bir işim var.";
			link.l1 = "Hangi iş? Çabuk konuş, acelem var.";
			link.l1.go = "PostAgent_1";
		break;
		
		case "PostAgent_1":
			dialog.text = "Kim olduğunu biliyorum. Ve ayrıca az önce bir  aldığını da biliyorum."+pchar.questTemp.WPU.Current.Add+" "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" . Bu belgeler, sizinle konuşmak için bu kadar hevesli olmamın sebebi.";
			link.l1 = "Ve bu konuyu tanımadığım insanlarla tartışmak istemiyorum. O belgeleri almak mı istiyorsun? Bana sadece bir sebep söyle...";
			link.l1.go = "PostAgent_2";
		break;
		
		case "PostAgent_2":
			dialog.text = "Yeter artık, kaptan! Soyguncuya mı benziyorum? Ben bir iş adamıyım ve çıkarları temsil ediyorum "+NationNameGenitive(sti(pchar.questTemp.WPU.Postcureer.EnemyNation))+". Sana çok kârlı bir teklif sunmak istiyorum, ama burada değil. Hadi meyhanenin odasına geçelim ve bu meseleyi orada konuşalım. Fazla vaktini almayacak.";
			link.l1 = "Bu fazlasıyla şüpheli... Sizinle hiçbir işim olmaz, bayım! Defolun!";
			link.l1.go = "PostAgent_getout";
			link.l2 = "Hm... Bakalım bana ne sunabilirsin. Ama sakın bana saldırmayı düşünme — sonu iyi olmaz. Hadi gidelim, seni takip edeceğim.";
			link.l2.go = "PostAgent_3";
		break;
		
		case "PostAgent_getout":
			dialog.text = "Sen inatçı ve aptal bir adamsın, kaptan! Sana kolay yoldan para kazanma fırsatı sundum. Ve sen... sen buna pişman olacaksın.";
			link.l1 = "Defol!";
			link.l1.go = "PostAgent_getout_exit";
		break;
	
		case "PostAgent_3":
			dialog.text = "Harika! Beni takip et.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			NextDiag.TempNode = "PostAgent_inTavern";
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", pchar.questTemp.WPU.Postcureer.StartCity +"_tavern_upstairs", "goto", "goto1", "PostAgent_inTavern_Room", -1);
		break;
		
		case "PostAgent_getout_exit":
			bDisableFastReload = false; 
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10);
			pchar.questTemp.WPU.Postcureer.AgentIslandID = GetCharacterCurrentIslandId(pchar);
			pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
			pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.AgentIslandID;
			pchar.quest.Postcureer_Hunter.function = "PostcureerAgent_ShipAttack";
			AddQuestRecord("Postcureer", "13");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "PostAgent_inTavern":
			dialog.text = "Artık özgürce konuşabiliriz.";
			link.l1 = "Peki, teklifiniz nedir?";
			link.l1.go = "PostAgent_inTavern_1";
		break;
		
		case "PostAgent_inTavern_1":
			dialog.text = "Dediğim gibi, bu tamamen liman ofisinde aldığın belgelerle ilgili. Tek ihtiyacım olan onların bir kopyası, hepsi bu\nOrijinaller sende kalacak, böylece işin karşılığını alacaksın. Kimse ne olduğunu asla bilmeyecek, ayrıca sana iyi bir ödeme yapacağım.";
			link.l1 = "Affedersiniz... Ama paket mühürlü. Mührü kırmadan kopya çıkarmanız mümkün değil!";
			link.l1.go = "PostAgent_inTavern_2";
		break;
		
		case "PostAgent_inTavern_2":
			dialog.text = "Bu soruyu bekliyordum. Mührü kırmam gerekecek, ama merak etme, onu tekrar eski haline getirebilirim. Elimde yedek bir klişe ve mühür mumu var tabii ki. Paketin açıldığını kimse fark etmeyecek.";
			link.l1 = "Limandaki yönetim hakkında yanlış bir klişen var mı "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"?";
			link.l1.go = "PostAgent_inTavern_3";
		break;
		
		case "PostAgent_inTavern_3":
			pchar.questTemp.WPU.Postcureer.AgentMoney = sti(pchar.rank)*3500;
			dialog.text = "Neden soruyorsun, kaptan? Evet, bir tane var. Gerçekten sadece oyalanıyor muyum sanıyorsun? Sana sunuyorum "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+" bu belgeleri görme fırsatı için. Peki, sonunda paketi bana verecek misin? Lütfen.";
			link.l1 = "Al bunu, ama onları geri istiyorum, hem de mühürlü olarak!";
			link.l1.go = "PostAgent_inTavern_4";
			link.l2 = "Biliyor musun, yapmam. Hoşuma gitmiyor.";
			link.l2.go = "PostAgent_inTavern_getout";
		break;
		
		case "PostAgent_inTavern_4":
			dialog.text = "Endişelenme. Ben profesyonelim. Otur ve biraz dinlen. Yaklaşık bir saat sürecek.";
			link.l1 = "Pekala.";
			link.l1.go = "PostAgent_inTavern_5";
		break;
		
		case "PostAgent_inTavern_5":
			NextDiag.currentnode = "PostAgent_inTavern_6";
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			pchar.questTemp.WPU.Postcureer.AgentChance = hrand(4);//шанс, что раскроют обман - 20%
			DialogExit();
			AddDialogExitQuest("PostAgent_inTavern_Room_end");
		break;
		
		case "PostAgent_inTavern_getout":
			dialog.text = "Hm... Bunu beklemiyordum. Çok inatçısın kaptan, bu yüzden seni olduğun yerde öldürüp paketi bedavaya alacağım. Dua et, çünkü kılıcımla da en az sahte laflarım kadar ustaca çalışırım.";
			link.l1 = "Sen dua etmelisin, casus!";
			link.l1.go = "PostAgent_inTavern_fight";
		break;
		
		case "PostAgent_inTavern_6":
			dialog.text = "Tamam. Dediğim gibi, iş en doğru şekilde yapıldı. Paketi söz verdiğim gibi al "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+". Ve gitmem gerek. İyi şanslar kaptan, anlaşmaya vardığımıza sevindim.";
			link.l1 = "Elveda...";
			link.l1.go = "PostAgent_inTavern_7";
		break;
		
		case "PostAgent_inTavern_7":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false; 
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.AgentMoney));
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			sld = characterFromID("PostAgent");        
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 2);
			AddQuestRecord("Postcureer", "15");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)));
		break;
		
		case "PostAgent_inTavern_fight":
			bDisableFastReload = false;
			sld = characterFromID("PostAgent"); 
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Postcureer", "16");
		break;
	//<-- почтовый генератор 2 уровня
		
	// --> --------------------------------- эскорт 2 уровень --------------------------------------------------
		case "DisasterCap":
			dialog.text = "Selam! Sizi gördüğüme çok sevindim!";
			link.l1 = "İyi günler. Hm, söyleyin bakalım, şu   "+pchar.questTemp.WPU.Escort.ShipName+"?";
			link.l1.go = "DisasterCap_1";
		break;
		
		case "DisasterCap_1":
			dialog.text = "Ah! Peki bunu nasıl öğrendin "+pchar.questTemp.WPU.Escort.ShipName+"Evet, ben onun kaptanıyım. Ya da öyleydim... Gemi buradan çok uzakta batmadı.";
			link.l1 = "Ah, demek seni buldum... Kendimi tanıtmama izin ver - "+GetFullName(pchar)+". Liman müdürünün isteği üzerine buradayım "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". Karavanınızın başına gelenleri kısaca anlattı ve geminizi bulmam için beni gönderdi.";
			link.l1.go = "DisasterCap_2";
		break;
		
		case "DisasterCap_2":
			dialog.text = "Demek kurtarma ekibinin kaptanısın?";
			link.l1 = "Öyle denebilir. Benim görevim, geminizi ya da onun battığına veya artık yelken açamayacak halde olduğuna dair bir kanıt bulmaktı. Ne yazık ki gemiyi bulamadım, ama kaptanı hayatta ve bu kesinlikle iyi bir haber...";
			link.l1.go = "DisasterCap_3";
		break;
		
		case "DisasterCap_3":
			dialog.text = "Ah, özür dilerim, kendimi tanıtmayı unuttum. Ben "+GetFullName(npchar)+" . Buraya nasıl düştüğümüzü zaten biliyor musun? Fırtına gemimizi kontrol edilemez hale getirdi\nBirkaç gün sonra, gemi bu koydan çok uzakta olmayan kayalıklara çarptı ve kasırga onu dakikalar içinde parçaladı. Mürettebatımdan sadece birkaç düzine kişi kurtuldu. Geri kalanı denizin dibinde yatıyor. Her gün ruhları için dua ediyoruz...";
			link.l1 = "Başınız sağ olsun, Kaptan "+GetFullName(npchar)+". Çok üzgünüm.";
			link.l1.go = "DisasterCap_4";
		break;
		
		case "DisasterCap_4":
			dialog.text = "Thank you... The survivors have set up a camp on the shore, hoping for aid. You are just in time, captain! The local warlike Indians are aware of our presence; we will not stand a chance against hundreds of them if they attack us.\nThere is also a pirate ship cruising in this area; it looks like they are searching for us. Have you encountered this pirate, captain?";
			link.l1 = "Hayır, yapmadım.";
			link.l1.go = "DisasterCap_5";
		break;
		
		case "DisasterCap_5":
			dialog.text = "Tanrı'ya şükürler olsun. O, o lanet fırtınadan önce bize saldıranlardan biri. Bir sırtlan gibi, yaralı avını bitirmek için sabırsızlanıyor, bu yüzden buraya, bu adaya geldi.";
			link.l1 = "Anladım. Şimdi sırada ne yapacağımıza karar vermek var.";
			link.l1.go = "DisasterCap_6";
		break;
		
		case "DisasterCap_6":
			dialog.text = "Ne hakkında karar vereceğiz, kaptan? Bizi gemiye al ve şu lanetli yerden uzaklaşalım.";
			link.l1 = "Kesinlikle. Gemiyi kurtaramadım ama en azından mürettebatını kurtaracağım. Kampınızı toplayın, buraya sandallar göndermelerini emredeceğim. Gemimize hoş geldiniz!";
			link.l1.go = "DisasterCap_7";
		break;
		
		case "DisasterCap_7":
			PlaySound("people fight\rifle_fire1.wav");
			PlaySound("people fight\player_man_shoot_01.wav");
			dialog.text = "Teşekkürler, kaptan! Uzun sürmeyecek. Bekle... Ne oluyor? Kahretsin! O kızıl derili şeytanlar yine peşimize düştü! Alarm! Silah başına!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_IndianAttack");
		break;
		
		case "DisasterCap_8":
			dialog.text = "Vay be, başardık... Bak kaptan, sana söylemiştim bu koy tam bir cehennem. Bu üçüncü Kızılderili saldırısı oldu! Buradan bir an önce gitmeliyiz, bir saldırıya daha dayanamayız.";
			link.l1 = "Evet, haklısın. Hayattaki herkesi toplayın ve gemime getirin! Hemen bizim için sandallar gönderilmesini emredeceğim!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_onBoard");
			AddQuestRecord("Escort", "38");
			AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore));
		break;
	// <-- эскорт 2 уровень
		
	//Jason --> -------------------------- Заносчивый аристократ ------------------------------------------------
		case "Badboy":
			dialog.text = "Hıç... Benden ne istiyorsun? Defol git, seninle konuşmak istemiyorum.";
			link.l1 = "Sen misin "+pchar.GenQuest.Badboy.Brothel.Name+"?";
			link.l1.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "Evet, öyleyim. Peki, sizin işiniz nedir?";
			link.l1 = "Oldukça basit. Bu kasabada senin numaralarından bıkan biri var. Artık seninle uğraşmak istemiyor. Şimdi sana bakınca sebebini anlıyorum. Bir daha asla buradaki geneleve uğrama, yoksa başın belaya girer. Anladın mı?";
			link.l1.go = "Badboy_2";
		break;
		
		case "Badboy_2":
			switch (sti(pchar.GenQuest.Badboy.Brothel.Type))
			{
				case 0://или напугается, или будет быковать - от авторитета
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 30)
					{
						dialog.text = "Argh! Bana... meydan okumaya cüret mi ediyorsun, seni alçak? Seni kılıcıma geçirip tavuk gibi şişte kızartacağım!";
						link.l1 = "Kendini hazırla, seni alçak!";
						link.l1.go = "Badboy_fight_1";
						NextDiag.currentnode = "Badboy_after_fight";
					}
					else
					{
						dialog.text = "Ne? Ne hilesi? Hiçbir hile yoktu. Birkaç kez genelevde sarhoş olup eğlendim. Kimse mükemmel değildir... Tamam, tamam, tamam... Bir daha asla onların hizmetlerinden yararlanmayacağım. Şimdi memnun musun? Söz veriyorum.";
						link.l1 = "Umarım şeref sözü senin için bir anlam ifade ediyordur ve bozarsan sonuçlarının farkındasındır. Bunu aklında tut. Şimdi hoşça kal.";
						link.l1.go = "exit";
						pchar.GenQuest.Badboy.Complete = "true";
						LAi_CharacterDisableDialog(npchar);
						npchar.lifeday = 0;
					}
				break;
				case 1://дуэль за городом
					dialog.text = "Ne kadar küstah bir adamsınız, efendim! Yemin ederim, gün batmadan sözlerinize pişman olacaksınız. Size meydan okuyorum! Sanırım en iyisi, sakin bir yerde, baş başa dövüşmemiz. Orman gayet uygun, iki saat sonra orada buluşalım!";
					link.l1 = "Harika bir fikir! En azından cesedini saklamak sorun olmazdı.";
					link.l1.go = "Badboy_duel";
					NextDiag.currentnode = "Badboy_duel_1";
					break;
				case 2://призовет на помощь дружков
					dialog.text = "Ne? Ne numarası? Hiçbir numara yoktu. Birkaç kez genelevde sarhoş olup kendimi kaybettim. Kimse mükemmel değil... Tamam, tamam, tamam... Bir daha asla onların hizmetlerinden yararlanmayacağım. Şimdi memnun musun? Söz veriyorum.";
					link.l1 = "Umarım şeref sözü senin için bir anlam ifade ediyordur ve eğer bozarsan bunun sonuçlarının farkındasındır. Bunu aklında tut. Şimdi hoşça kal.";
					link.l1.go = "exit_continue";
					pchar.GenQuest.Badboy.Continue = "true";
					NextDiag.currentnode = "Badboy_friends";
				break;
			}
		break;
		
		case "Badboy_fight_1":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("Badboy");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(npchar, 10.0, true, "Badboy_capture");
			DialogExit();
		break;
		
		case "Badboy_after_fight":
			dialog.text = "Dur! Durun! Teslim oluyorum! Beni bağışlayın!";
			link.l1 = "Ve şimdi böyle mi konuşuyorsun!";
			link.l1.go = "Badboy_after_fight_1";
		break;
		
		case "Badboy_after_fight_1":
			dialog.text = "Lütfen, yalvarırım, bana acı! Ne istersen yaparım! Bir daha o geneleve asla gitmem!";
			link.l1 = "Bu tavır ancak senin gibi pisliklere yakışır. Umarım bu sana hayatının geri kalanı için bir ders olur. Ve bu kasabada kendine çeki düzen ver.";
			link.l1.go = "Badboy_exit";
			link.l2 = "Emin ol, yapamazsın. Hilelerin burada ve şimdi sona eriyor.";
			link.l2.go = "Badboy_killed";
			pchar.GenQuest.Badboy.Complete = "true";
		break;
		
		case "Badboy_exit":
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;
		
		case "Badboy_killed":
		DialogExit();
		LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
		LAi_ActorAnimation(pchar, "shot", "Badboy_killed_end", 2.2);
		break;
		
		case "Badboy_duel":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationDisableOfficersGen(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown", true);//офицеров не пускать
			locations[FindLocation(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown")].DisableEncounters = true; //энкаутеры закроем
			pchar.quest.BadboyDuelTimer.win_condition.l1 = "Timer";
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.BadboyDuelTimer.function = "Badboy_duelstart";
			sld = characterFromId("Badboy");
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			TakeNItems(sld, "jewelry5", rand(10)); 
			TakeNItems(sld, "jewelry3", rand(10)); 
			TakeNItems(sld, "jewelry1", rand(10)); 
			sld.money = 24560;
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			LAi_RemoveLoginTime(sld); //удалить время логина
			SetFunctionTimerCondition("Badboy_duelOver", 0, 0, 1, false);
			DialogExit();
		break;
		
		case "Badboy_duel_1":
			dialog.text = "Cehenneme gitme vakti, alçak! Kendin için dua et, ama çabuk ol, bütün lanet günü bekleyecek değilim...";
			link.l1 = "Daha az konuş, daha çok dövüş, pislik!";
			link.l1.go = "Badboy_duel_2";
		break;
		
		case "Badboy_duel_2":
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Badboy_die");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_continue":
			sld = characterFromID("Badboy");        
			LAi_RemoveLoginTime(sld); // patch-6
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;		
		
		case "Badboy_friends":
			dialog.text = "Ve işte orada, o küstah herif! Hadi ona bu kasabanın kime ait olduğunu gösterelim, çocuklar!";
			link.l1 = "Ah, tam bir sefilsin! Ama seni uyarmıştım. Sen ve maymunların birazdan doğrudan cehenneme gideceksiniz!";
			link.l1.go = "Badboy_friends_fight";
		break;
		
		case "Badboy_friends_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			DeleteAttribute(pchar, "GenQuest.Badboy");
		break;
	//Jason <-- Заносчивый аристократ
		
	//Jason --> ------------------------------- Место под солнцем ----------------------------------------------
		case "Sunplace_Store":
			pchar.quest.SunplaceContinue_Over.over = "yes";
			dialog.text = "Selam. Ne istiyorsun?";
			link.l1 = "Sen değil misin "+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Bana inanmayacaksın, haha. Kafanı istiyorum.";
			link.l1.go = "Sunplace_Store_1";
			link.l2 = "Hm... Hayır... Bir şey değil. Sanırım yanılmışım. Sizi rahatsız ettiğim için affedin.";
			link.l2.go = "Sunplace_Store_exit";
		break;
		
		case "Sunplace_Store_1":
			dialog.text = "Ne saçma bir şaka bu, efendim! Açıklayın kendinizi yoksa...";
			link.l1 = "Ve sen ne yapacaksın, zavallı ringa balığı? İyi bir adama kötülük ettin ve o gerçekten üzgün. Şimdi dua et ve çabuk ol, çünkü acelem var.";
			link.l1.go = "Sunplace_Store_3";
		break;
		
		case "Sunplace_Store_3":
			dialog.text = "Ne... ne yapıyorsunuz, efendim! Yardım edin! Birisi yardım etsin! Katil!";
			link.l1 = "And I thought you would spend your last seconds praying; at least you might have had a chance to reach the heavens...";
			link.l1.go = "Sunplace_Store_fight";
		break;
		
		case "Sunplace_Store_exit":
			sld = CharacterFromID("SunplaceTrader");
			sld.lifeday = 0;
			AddQuestRecord("Sunplace", "9");
			CloseQuestHeader("Sunplace");
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			NextDiag.currentnode = "Sunplace_Store_repeat";
		break;
		
		case "Sunplace_Store_repeat":
			dialog.text = "Yine sen mi? Neden bana ne istediğini söylemiyorsun?";
			link.l1 = "Önemli bir şey değil.";
			link.l1.go = "exit";
		break;
		
		case "Sunplace_Store_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("SunplaceTrader");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, Pchar, true);
			sld = characterFromId(pchar.GenQuest.Sunplace.Trader.CityT + "_trader");
			LAi_group_Attack(sld, Pchar);
			pchar.quest.Kill_SunplaceTrader.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Kill_SunplaceTrader.win_condition.l1.location = pchar.location;
			pchar.quest.Kill_SunplaceTrader.function = "Kill_SunplaceTrader";
		break;
	// <-- место под солнцем
		
	//------------------------------------- киллеры Лиги-------------------------------------------------------
		case "LigaHunters":
			dialog.text = "";
			link.l1 = "Ah?! Ne? Ne halt ediyorsun burada, kahretsin seni? Kim soktu seni içeriye?";
			link.l1.go = "LigaHunters_1";
		break;
		
		case "LigaHunters_1":
			dialog.text = "Liga senin hayatını istiyor, kaptan...";
			link.l1 = "Ne? Kahretsin!";
			link.l1.go = "LigaHunters_2";
		break;
		
		case "LigaHunters_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("LigaHunter_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "LigaHunters_Dead");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	// <-- киллеры Лиги
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
			dialog.text = NPCharSexPhrase(NPChar,"Dinle, ben bu kasabanın bir vatandaşıyım ve senden kılıcını kınına koymanı istiyorum.","Dinle, ben bu kasabanın bir vatandaşıyım ve senden kılıcını kınına sokmanı istiyorum.");
			link.l1 = LinkRandPhrase("Pekala.","Pekala.","Tabii...");
			link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dikkatli ol, "+GetSexPhrase("ahbap","kız")+", silahla koşarken. Geriliyorum...","Ortalıkta  olduğunda  hoşuma gitmiyor "+GetSexPhrase("adamlar ki","insanlar ki")+" önümde silahları hazır bir şekilde yürüyorlar. Bu beni korkutuyor...");
				link.l1 = LinkRandPhrase("Anladım.","Sorun değil.","Endişelenme...");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
			if (npchar.id == "Device_poorman") NextDiag.TempNode = "Device_poorman";
		break;
	}
}
