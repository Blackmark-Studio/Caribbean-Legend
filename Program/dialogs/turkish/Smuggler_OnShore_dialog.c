void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;	
	int Shit, i;
	ref refStore;
	ref sld;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
        case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

        case "First time":
			Diag.TempNode = "first time";
			if(CheckAttribute(PChar, "quest.Contraband.active"))
			{
				int iTmp = false;
				int iChIdx;
				
				float fMaxClass = ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5);
				if (IsEquipCharacterByArtefact(pchar, "talisman21")) fMaxClass = 2.0;
				
				if (GetCompanionQuantity(pchar) > 1) iTmp = true;
				if (GetCharacterShipClass(pchar) < fMaxClass) iTmp = true;

				// поиск мин.  те старшего класса
				/* for (i=0; i<COMPANION_MAX; i++)
				{
					iChIdx = GetCompanionIndex(GetMainCharacter(), i);
					if (iChIdx>=0)
					{
						sld = GetCharacter(iChIdx);
            			if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
					}
				} */
				
				if (iTmp)
				{
					dialog.text = NPCStringReactionRepeat("Sana böyle göze çarpan bir gemiyle buraya gelmemen söylenmedi mi! Neden yanında iki savaş gemisi daha getirmiyorsun? Kaybol da daha küçük bir gemiyle geri gel.","Defol! Yoksa seni bizzat devriyeye teslim ederiz.","Teknenize gidin ve buradan uzaklaşın.","Senden o kadar yoruldum ki...","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Pekala, pekala, gemimi değiştireceğim.","Sakin ol, geliyorum.","Lanet olsun, işe yarayacağını sanmıştım...","Evet, gerçekten inatçıyım!",npchar,Dialog.CurrentNode);
						link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
					break;
				}
			
				Dialog.snd = "voice\SMSH\SMSH001";
				dialog.Text = RandPhraseSimple("Hey, burada ne yapıyorsun, "+GetSexPhrase("kanka","kız")+"?",RandSwear()+"Burada ne işin var?!");
				Link.l1 = "Sakin ol dostum, hadi ticaret yapalım!";
				Pchar.quest.Contraband.Counter = 0; // не торговали
				if(Pchar.Location == Pchar.location.from_sea)
				{
					Link.l1.go = "Exchange";
				}
				else
				{
					Link.l1.go = "No_Ship";
				}
				//по заданию губернатора, истребление контры, только эта ветка.
				if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))				
				{
					Link.l2 = "Valinin emriyle buradayım "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen")+"Silahlarını bırak ve beni takip et, tutuklusun!";
					Link.l2.go = "GenQuestKillContraband_1";
				}
			}
			else
			{
//================ METRO ====================
				//если заплатил, то разговаривают, иначе посылают
				if (CheckAttribute(PChar, "GenQuest.contraTravel.payed") && sti(PChar.GenQuest.contraTravel.payed) == true)
				{
                    dialog.Text = RandPhraseSimple("Ah, sonunda! Seni bekliyorduk. Hadi, artık yelken açma zamanı.","Hadi hızlıca halledelim. Her yerde devriyeler var. Buradan uzaklaşmamız lazım!");
					//по заданию губернатора, истребление контры, только эта ветка.
					if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))
					{
						Link.l1 = "Valinin emriyle buradayım "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen")+"Silahlarınızı bırakın ve beni takip edin, tutuklusunuz!";
						Link.l1.go = "GenQuestKillContraband_1";
						break;
					}
					//если набрал пассажиров, в сад..
					if (GetPassengersQuantity(PChar) > 0)
					{
						dialog.Text = "Sen de kimsin? Biz sadece bir yolcudan bahsediyorduk!";
						Link.l1 = "Hay aksi..";
						Link.l1.go = "Exit";
						break;
					}
					//если набрал компаньонов или купил корабль себе уже :), в сад..
					if (GetCompanionQuantity(PChar) > 1 || sti(PChar.ship.type) != SHIP_NOTUSED)
					{
						dialog.Text = RandPhraseSimple("Sen kimsin? Biz bir yolcu bekliyorduk, kaptan değil.","Defol! Geminden kurtulmadan geri dönme.");
						Link.l1 = "Kahretsin!";
						Link.l1.go = "Exit";
						break;
					}
					//типа помог отбиться, свой парень... 
					if (CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight") && sti(PChar.GenQuest.contraTravel.PatrolFight) == true)
					{
						if (chrDisableReloadToLocation) // ещё бой идёт
						{
						    dialog.Text = "Lanet olsun, devriye! Biz seni tanımıyoruz, sen de bizi tanımıyorsun.";
							Link.l1 = "Peki...";
							Link.l1.go = "Exit";
							break;
						}
						dialog.Text = RandPhraseSimple("Yardımınız için teşekkürler. Bunu unutmayacağız. Şimdi yelken açalım.","Aferin! Güzel dövüştün. Hadi gidelim.");
						ChangeContrabandRelation(PChar, 5);
						PChar.GenQuest.contraTravel.PatrolFight = false;
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
					//тут все ок, отправляемся.
					Link.l2 = "Yoldayım.";
					Link.l2.go = "Exit";
					//а это патруль... 
					if (GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < frandSmall(13.0*(1.0 - pow(0.9, sti(PChar.rank)))) && !CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight"))
					{
						AddDialogExitQuest("Rand_ContrabandInterruption");
						PChar.GenQuest.contraTravel.PatrolFight = true;
					}
					else 
					{
						//поместим Грея в локацию.
						refStore = CharacterFromID("Abracham_Gray");
						ChangeCharacterAddressGroup(refStore, "Ship_deck", "goto", "goto2");
						refStore.dialog.Filename = "Smuggler_Ship_dialog.c";
                        refStore.dialog.CurrentNode = "Travel_talkStart";
						//поплыл, иначе RemoveTravelSmugglers грохнет всю ветку
						PChar.GenQuest.contraTravel.ship = true;
						PChar.quest.Munity = "";  // признак выхода с палубы
						
						SetLaunchFrameFormParam(".. " + sti(Pchar.GenQuest.contraTravel.destination.days) + " days passed." + NewStr() + "Smuggler's ship deck.",
						                        "Reload_To_Location", 0.1, 5.0);
                        bQuestCheckProcessFreeze = true;
						WaitDate("", 0, 0, sti(Pchar.GenQuest.contraTravel.destination.days), rand(20), 0);
						bQuestCheckProcessFreeze = false;
						MakeCloneShipDeck(refStore, true); // подмена палубы
						SetLaunchFrameReloadLocationParam("Ship_deck", "reload", "reload1", "Travel_talkOnDeck");
						AddDialogExitQuest("LaunchFrameForm");
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
//================ METRO ====================
				}
				else
				{
                    // если таможня уже бежит
					if (CheckAttribute(NPChar, "ContrabandInterruption"))
					{
					    dialog.Text = RandSwear()+"Devriye! Biz seni tanımıyoruz, sen de bizi tanımıyorsun.";
						Link.l1 = "Pekâlâ!";
						Link.l1.go = "Exit";
					}
					else
					{
						dialog.Text = "Defol git! Anlaşmamıza karışırsan bağırsaklarını deşeriz.";
						Link.l1 = RandPhraseSimple("Bana tehdit mi savuruyorsun, köpek!?","Sözlerinle boğulacaksın!");
						Link.l1.go = "Exit_fight";
						Link.l2 = "Merak etme, işlerin nasıl yürüdüğünü biliyorum. Hoşça kal.";
						Link.l2.go = "Exit";
					}
				}
			}
		break;

		case "No_Ship":
			Dialog.snd = "voice\SMSH\SMSH003";
			dialog.Text = "Sırtında mı taşıyorsun? Gemin nerede?";
			Link.l1 = RandPhraseSimple("Öncelikle, bunda bir bit yeniği var mı görmek isterim.","Gemiyi riske atmak istemedim. Her şeyi kendi gözlerimle görmeyi tercih ederim.");
			Link.l1.go = "No_ship_1";
			Link.l2 = "Anlaşma bitti!";
			Link.l2.go = "Cancellation";
		break;

		case "No_ship_1":
			Dialog.snd = "voice\SMSH\SMSH004";
			dialog.Text = "Biz dürüst insanlarız ve seni kandırmayız. Gemini buraya getir, ama devriyelerin seni takip etmesine izin verme.";
			Link.l1 = "Pekâlâ. Burada beni bekle.";
			Link.l1.go = "Exit";
		break;

		case "Cancellation":
            if (sti(Pchar.quest.Contraband.Counter) == 0)
            {
    			dialog.Text = "Bitti mi? Şaka yapıyor olmalısın!";
    			Link.l1 = "Ciddiyim.";
    			Link.l1.go = "Cancellation_1";
			}
			else
            {
    			dialog.Text = "Pekâlâ o zaman. Zaten bugün iyi ticaret yaptık.";
    			Link.l1 = "Doğru!";
    			Link.l1.go = "Finish_exit";
			}
		break;

		case "Cancellation_1":
			if( makeint(Pchar.rank) <= 3 || GetSummonSkillFromNameToOld(Pchar, SKILL_FENCING) <= 5 || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) <= 5 )
			{
				if(Rand(1) == 1)
				{
					ChangeContrabandRelation(pchar, -30);
					Dialog.snd = "voice\SMSH\SMSH006";
					dialog.Text = "Seni alçak! Bizi bu kadar kolay kandıramazsın! Bunun bedelini canınla ödeyeceksin!";
					Link.l1 = "Hiç sanmam!";
					Link.l1.go = "Exit_fight";			
				}
				else
				{
					ChangeContrabandRelation(pchar, -10);
					Dialog.snd = "voice\SMSH\SMSH007";
					dialog.Text = "Bununla paçayı sıyıramayacaksın!";
					Link.l1 = "Defolun buradan, köpekler!";
					Link.l1.go = "Exit_cancel";
				}
			}	
			else
			{
				ChangeContrabandRelation(pchar, -10);
				Dialog.snd = "voice\SMSH\SMSH008";
				dialog.Text = "Bunu pişman olacaksın!";
				Link.l1 = "Çok konuşuyorsun.";
				Link.l1.go = "Exit_cancel";			
			}	
		break;

		case "GenQuestKillContraband_1":
			//счетчик подстав по "метро"...
			if(CheckAttribute(PChar, "GenQuest.contraTravel.active") && sti(PChar.GenQuest.contraTravel.active) == true)
			{
				Statistic_AddValue(PChar, "contr_TravelKill", 1);
				ChangeContrabandRelation(pchar, -20); //репу контры вниз
			}
			dialog.Text = "Bunun hesabını vereceksin!";
			Link.l1 = "O halde hepiniz ölüsünüz. Emirlerim açık - eğer karşı koyarsanız, hepinizi yok edeceğim.";
			Link.l1.go = "Exit_fight";
		break;
		
		case "Exit_Cancel":
            DeleteAttribute(Pchar, "quest.Contraband");
            CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;
		
		case "Exit_fight":
            DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");			

			AddSimpleRumourCity("Heard the latest news? The local smugglers were rounded up by a patrol not long ago. And you know what? Captain who had a deal with them escaped!" +
				"He had dashing lads in his crew and the whole patrol was killed. And our local smugglers just vanished. There was nothing found on the shore. No goods, no stash and smugglers. See, how they do their business here!", Pchar.quest.contraband.City, 3, 5, "");	

			CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			LAi_group_FightGroups(LAI_GROUP_PLAYER, pchar.GenQuest.Smugglers_Group, true);
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			LAi_SetFightMode(Pchar, true);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "Finish_exit":
            // таможня на суше
            if(GetSummonSkillFromName(pchar, "Sneak") < Rand(120))
			{
				AddDialogExitQuest("Rand_ContrabandInterruption");
				for (i=1; i<=3; i++)
				{
					characters[GetCharacterIndex("Rand_Smug0"+i)].ContrabandInterruption = true;
				}
			}
			AddCharacterExpToSkill(Pchar, "Sneak", 100);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			ChangeContrabandRelation(pchar, 15);
            OfficersReaction("bad");
            ChangeCharacterComplexReputation(pchar,"nobility", -1);
            
            CloseQuestHeader("Gen_Contraband");
            
			DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");
	
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
		break;

		case "Exchange":
			// сама торговля -->
            if(FindContrabandGoods(Pchar) == -1 && sti(Pchar.quest.Contraband.Counter) == 0)
            {
				dialog.Text = "Ve sen burada ne yapıyorsun? Satacak hiçbir şeyin yok! Yükündeki her şey kasabada satılabilir!";
				Link.l1 = "Bu sefer şansımız yaver gitmedi.";
				Link.l1.go = "NoGoods";
			}
			else
			{
                // установим окружение -->
                if (sti(Pchar.quest.Contraband.Counter) == 0) // не торговали ещё
                {
                    if(hrand(11) == 3)
                    {
        				dialog.Text = "Anladım... Biliyor musun, mallarını bedavaya alacağız. Zaten şikayet edebileceğini sanmıyorum.";
        				Link.l1 = "Denesene, pislik!";
        				Link.l1.go = "Exit_fight";
                        break;
        			}
        			// море и солдаты на суше НЕЗАВИСИМЫ!!!
        			if(GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < Rand(12))
        			{
                        SetCoastalGuardPursuit();
        			}
        			// при убегании от патруля на карту - корабли трем
        			SetTimerCondition("Rand_ContrabandInterruptionAtSeaEnded", 0, 0, 2, false);// если в порту сидим, спим, то 2 день
        			
                    Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition.l1 = "MapEnter";
        			Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition = "Rand_ContrabandAtSeaEnded";
    			}
    			// установим окружение <--
				dialog.text = "Pekala, neyin var görelim.";										  
				Link.l1 = "Bize neler yapabileceğini göster.";
				Link.l1.go = "Exchange1"; 
				if (sti(Pchar.quest.Contraband.Counter) == 0)
    			{
        			Link.l99 = "Fikrimi değiştirdim.";
    				Link.l99.go = "Cancellation";
				}				
            }
		break;
		
		case "Exchange1":
			NPChar.quest.meeting = NPC_Meeting;
			Diag.CurrentNode = Diag.TempNode;		 
			DialogExit();
			// belamour legendary edition опасный груз
			pchar.GenQuest.Smugglerzpq = npchar.id;
			
			LaunchContrabandTrade(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId),  sti(pchar.FindContrabandGoods.StoreIdx));	
		break;				
		// belamour legendary edition опасный груз -->
		case "SmugglerZPQ":
			dialog.text = "Güzel anlaşma, kaptan! Başka ilginç mallarınız olursa, bize haber verin!";										  
			Link.l1 = "Katılıyorum, ben de ticaretimizden memnunum. Ah, keşke tüm mallarımı böyle iyi bir fiyata alabilsem...";
			Link.l1.go = "SmugglerZPQ_1"; 
		break;

		case "SmugglerZPQ_1":
			dialog.text = "Neden sıradan malları bu fiyatlara alalım ki, yasal olarak dükkandan satın alınabiliyorken? Ama moralini bozma: aslında, her ürün satılabilir, sıradan barut bile! Yeter ki doğru yeri bil, göklere çıkaran bir fiyata satabilirsin.";										  
			Link.l1 = "Hadi ama. Kim barutu bu kadar fahiş bir fiyata alır ki?";
			Link.l1.go = "SmugglerZPQ_2"; 
		break;
		
		case "SmugglerZPQ_2":
			dialog.text = "Well, that's what I told you, hehe ... Although ... You know, there really is an opportunity to sell gunpowder for a fortune, but this deal still isn't for us; for that, you need to have a rather good reputation, and we, as you understand, are not nobles.";										  
			Link.l1 = "Pekala, belki bu işi araştırabilirim. Gerektiğinde iyi ve nazik olabilirim. Anlaşmadan bahsedebilir misin?";
			Link.l1.go = "SmugglerZPQ_3"; 
		break;
		
		case "SmugglerZPQ_3":
			dialog.text = "Bu dünyada her şeyin bir bedeli var, kaptan, bilgi de dahil. Hatta özellikle bilgi. Şöyle bir teklifim var: Sana bu ipucunu sembolik bir ücret karşılığında... diyelim ki beş bin peso karşılığında veririm. Uygun mudur?";										  
			Link.l1 = "Beş bin peso ödeyip barutun yüksek fiyata satılabileceği yeriyle ilgili şüpheli bir bilgi almak mı? Hayır, sanırım bu ipucu olmadan da idare edebilirim.";
			Link.l1.go = "SmugglerZPQ_NM"; 
			if(sti(pchar.money) > 4999)
			{
				Link.l2 = "Bu işten sadece beş bin değil, daha fazlasını kazanabileceğimi düşünüyorum. Peki, anlaştık.";
				Link.l2.go = "SmugglerZPQ_4";
			}
		break;	
		
		case "SmugglerZPQ_NM":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "Karar senin, kaptan. Her halükarda iyi bir anlaşma yaptık. Bol şans... ve devriyeye yakalanma sakın!";										  
			Link.l1 = "Sen de. Hoşça kal.";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_4":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Excellent, captain! You are an exceptional customer, you know. So listen. I heard whispers that in some of the Spanish cities on the Main, there is a problem with gunpowder. Whether it's tropical downpours or something else – in short, the fort guarding the colony has very little in reserve. And the commandant of this fort is looking for someone who could help him in this difficult situation.\nThere are only two problems: first, this is a delicate matter, and the commandant will not discuss it with just any rogue; and secondly, we are talking about a very large shipment – not every ship can carry so much gunpowder, so you might need a fleet. Also, not every captain will agree to turn his vessel into a floating bomb that could easily destroy an entire island if struck by a stray cannonball.";
			if(CheckAttribute(pchar,"questTemp.zpq"))
			{
				Link.l1 = "Üzgünüm, ama bu anlaşmadan zaten haberim var. Yine de, bu anlaşma paradan daha değerli, bu yüzden beş bin hak ediyorsun.";
				Link.l1.go = "SmugglerZPQ_5"; 
			}
			else
			{
				Link.l1 = "Değerli bilgiler, teşekkür ederim. Eğer Maine'de olursam, kalelerin yerel komutanlarına başlarına gelen talihsizlikleri sorarım. Ve bir şekilde ya bu sorunları çözerim ya da kendi çıkarıma kullanırım, hehe.";
				Link.l1.go = "SmugglerZPQ_6"; 
			}
		break;
		
		case "SmugglerZPQ_5":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "Böyledir bu işler. Her halükarda, iyi bir anlaşma yaptık. Bol şans... ve sakın devriyeye yakalanma!";										  
			Link.l1 = "Sen de. Hoşça kal.";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_6":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			AddQuestRecord("zpq", "0");
			dialog.text = "Böyledir bu işler. Her halükarda, iyi bir anlaşma yaptık. Bol şans... ve sakın devriyeye yakalanma!";										  
			Link.l1 = "Sen de. Hoşça kal.";
			Link.l1.go = "exit"; 
		break;
		// <-- legendary edition опасный груз
	}
}
