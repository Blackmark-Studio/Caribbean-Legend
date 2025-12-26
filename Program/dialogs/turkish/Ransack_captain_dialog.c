// BOAL диалог пленников - в трюме
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref offref;
    int i, cn;
    int qty;
    string attrLoc, sTmp;
    
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "First time":
		//--> Jason, Ложный след
		if (CheckAttribute(pchar, "questTemp.FalseTrace.Prisoner") && GetFullName(npchar) == pchar.questTemp.FalseTrace.CapName)
		{
			dialog.text = "Ne istiyorsun, kaptan? Fidye mi konuşacağız? Bilmeni isterim ki kızın kaderi benim için önemli...";
			link.l1 = "Katerine Rayner'dan mı bahsediyorsun? Zaten bundan haberim var, "+pchar.questTemp.FalseTrace.CapName+".   Benim seninle konuşmamı istedi.";
			link.l1.go = "FalseTrace_Prisoner";
			break;	
		}
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && CheckAttribute(pchar, "questTemp.FMQG.Prisoner") && GetFullName(npchar) == pchar.questTemp.FMQG.Prisoner)
		{
			dialog.text = "";
			link.l1 = "Bak şimdi, don Juan, ihanet alçak bir şeydir...";
			link.l1.go = "FMQG";
			break;	
		}
			if (sti(NPChar.nation) == PIRATE)
			{
				dialog.text = RandSwear()+"Ben senin tutsağınım, "+GetAddress_Form(NPChar)+". Ama bilmeni isterim ki "+NationNameNominative(sti(NPChar.nation))+" kendi insanlarının parasını asla ödemez. Hepimiz kendi başımızayız.";
				link.l1 = "Pekâlâ... Senden bir kazanç elde edemeyeceğim anlaşılan. En azından seni herhangi bir kolonide suçlu olarak fidye karşılığı teslim edebilirim.";
				link.l1.go = "offender";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l2 = "Bak, sen yetenekli bir savaşçısın ve benim gibi insanlara ihtiyacım var. Komutam altında hizmet etmek ister misin?";
					link.l2.go = "free_to_officer";
				}	
			}
			else
			{
				dialog.text = RandSwear()+"Ben senin tutsağınım, "+GetAddress_Form(NPChar)+". "+NationNameNominative(sti(NPChar.nation))+" özgürlüğüm için iyi bir bedel ödeyecek.";
				if(NPChar.EncType == "trade" && FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
				{
					link.l1 = "Bak, sen yetenekli bir denizcisin ve senin gibi insanlara ihtiyacım var. Komutam altında hizmet etmek ister misin?";
					link.l1.go = "free_to_officer_trader";
				}
			}
			attrLoc = Sea_FindNearColony();
			if (attrLoc != "none") 
			{
                link.l3 = "Çok uzakta değiliz "+GetCityName(attrLoc)+". Ve seni burada bırakabilirim.";
			    link.l3.go = "free_withoutFee";
			}
			else
			{
                link.l3 = "Çarkçıbaşıya git, sana bir dolap versin. Bir sonraki limanda karaya çıkabilirsin.";
			    link.l3.go = "free_withoutFee_2";
			}			
			link.l4 = "Sana iyi bir köle yapacağım sanırım - güçlü ve itaatkâr.";
			link.l4.go = "Slave_1";
			link.l5 = "Yelkenlerini indirmen emrini görmezden geldin ve güç kullanarak direndin. Bunun bedelini idamla ödeyeceksin. Başçavuşa çoktan talimatlarımı verdim.";
			link.l5.go = "PunishmentAction";
			link.l99 = "Biliyorum.";
			link.l99.go = "exit";
			NextDiag.TempNode = "second time"; 
		break;
		
		case "second time":
			if(CheckAttribute(NPChar,"Hold_GenQuest") && !CheckAttribute(pchar,"GenQuest.Hold_GenQuest"))
			{
				switch(sti(NPChar.Hold_GenQuest.variant))
				{				
					case 0: // "tip-off"
						dialog.text = RandPhraseSimple("Kaptan, fidyem yerine daha kârlı bir teklifimi duymak ister misiniz?","Burada pazarlık yapacak bir alan olmadığını anlıyorum, ama teklifimi duymak ister misiniz?");
						link.l1 = "Dinliyorum.";	
						link.l1.go = "free_tip_off";
					break;
					
					case 1:
						dialog.text = "Kaptan, neden beni bırakmıyorsun? Sana hiçbir faydam yok. Eğer beni köle tacirlerine satarsan, sadece birkaç kuruş alırsın ve kötü bir şöhret kazanırsın.";
						link.l1 = "Ve eğer seni öylece serbest bırakırsam, hiçbir şey elde edemem...";
						link.l1.go = "free_by_hoard";
						attrLoc = Sea_FindNearColony();
						if (attrLoc != "none") 
						{
							link.l2 = "Yelkenlerini indirmen emrini görmezden geldin ve güç kullanarak karşı koydun. Bunun bedelini idamla ödeyeceksin. Başçavuşa çoktan emirlerimi verdim.";
							link.l2.go = "PunishmentAction";							
						}
						else
						{
							link.l2 = "Gerçekten ısrarcısın, bu yüzden istediğini sana vereceğim. Artık özgürsün. Gemimden git.";
							link.l2.go = "free_in_sea";
						}
						link.l3 = LinkRandPhrase("Sabrımı zorlamayın. Hayatta olduğuna şükret.","Senin için kendi planlarım var.","Gelecekte bana hâlâ faydalı olabilirsin, sanırım.");
						link.l3.go = "exit";	
					break;
					
					case 2: // "ransom"
						dialog.text = "Kaptan, bu belirsizlik beni öldürüyor. Benimle ne yapmayı düşündüğünüzü öğrenebilir miyim?";
						link.l1 = "Bana sunacak bir şeyin var mı?";
						link.l1.go = "free_buyout";
						link.l2 = RandPhraseSimple("Senin hakkında henüz bir fikrim yok.",RandPhraseSimple("Planlar mı? Boynuna bir top gülle mi asayım? Şaka yapıyorum, ha!","Sen benim tutsağımsın ve seninle ne istersem yapmaya hakkım var. Burada senin fikrinin hiçbir önemi yok."));
						link.l2.go = "exit";
					break;										
				}
				NextDiag.TempNode = "second time"; 
			}
			else
			{
				if (sti(NPChar.nation) == PIRATE)
				{
					dialog.text = "Kaptan, neden beni bırakmıyorsun? Sana bir faydam yok. Korsan olmak tek seçeneğimdi, çünkü ne değerli bir yeteneğim var ne de bir eğitimim. Tek istediğim biraz para kazanıp sonra köşeme çekilmekti.";
					if (FindFreeRandomOfficer() > 0)
					{
						link.l2 = "Bak, sen yetenekli bir savaşçısın ve benim senin gibi gözü kara adamlara ihtiyacım var. Subayım olmak ister misin?";
						link.l2.go = "free_to_officer";
					}				
					link.l3 = LinkRandPhrase("Senin için merhamet yok. Denizde zaten yeterince haydut var. En azından artık bir tanesi eksilecek."," Bir sorun mu var, 'deniz kurdu'? Burada kal ve sessiz ol.","Tüm sizin gibiler darağacını boylayacak. Sizi yetkililere teslim edeceğim, bu da tüm korsanlara iyi bir ders olacak.");	
					link.l3.go = "exit";
				}
				else
				{
					if(NPChar.EncType == "trade")
					{
						dialog.text = "Kaptan, yalvarırım... Beni bırakın. Bir ailem ve çocuklarım var, onlar bensiz ne yapar bilmiyorum.";
						if (FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
						{
							link.l2 = "Bak, sen yetenekli bir denizcisin ve benim gibi insanlara ihtiyacım var. Komutam altında hizmet etmek ister misin?";
							link.l2.go = "free_to_officer_trader";
						}
						link.l3 = LinkRandPhrase("Senin için kendi planlarım var.","Sanırım gelecekte bana hâlâ faydalı olabilirsin.","Sen benim tutsağımsın ve seninle ne istersem yapmaya hakkım var.");
						link.l3.go = "exit";
					}
					if(NPChar.EncType == "war")
					{
						dialog.text = RandPhraseSimple("Kaptan, dövüşü kaybettim ve merhametinize sığınıyorum. ","Kaptan, merhametinize sığınıyorum. Biliyorum, beni savaş esiri olarak görmeniz için bir sebep yok. Bu yüzden size yalvarıyorum, bana acıyın. Size söz veriyorum, denizde bir daha karşınıza çıkmaktan kaçınacağım.");
						link.l2 = LinkRandPhrase("Sabrımı zorlamayın. Zaten hayatta olduğuna şükret.",RandPhraseSimple("Senin için kendi planlarım var.","Sanırım gelecekte bana hâlâ faydan dokunabilir."),RandPhraseSimple("Sen benim esirimsin ve seninle ne istersem yapmaya hakkım var. Senin fikrinin burada hiçbir değeri yok.","Sen... yani, bir savaş gemisinin kaptanısın ya da öyleydin ve risklerin farkındaydın. Burada kendini bir aziz gibi göstermeye çalışma."));
						link.l2.go = "exit";	
						if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 1)
						{
							if(sti(Items[sti(pchar.EquipedPatentId)].Nation) == sti(NPChar.nation) && FindFreeRandomOfficer() > 0)
							{
								link.l3 = "Bak, sen yetenekli bir dövüşçüsün ve benim senin gibi gözü kara adamlara ihtiyacım var. Subayım olmak ister misin?";
								link.l3.go = "free_to_officer";
							}
						}
					}
				}
				attrLoc = Sea_FindNearColony();
				if (attrLoc != "none") 
				{
					link.l4 = "Çok uzakta değiliz "+GetCityName(attrLoc)+". Ve seni burada bırakabilirim.";
					link.l4.go = "free_withoutFee";
				}
				else
				{
					if(NPChar.EncType == "trade" || NPChar.EncType == "pirate")
					{
						link.l4 = "Kamarotaya git, sana bir dolap versin. Bir sonraki limanda karaya çıkabilirsin.";
						link.l4.go = "free_withoutFee_4";			
					}	
					else
					{
						link.l4 = "Lanet olsun sana! Git lostromosa, sana bir ranza versin. Bir sonraki limanda inebilirsin. Ve unutma, bir dahaki karşılaşmamız son olacak.";
						link.l4.go = "free_withoutFee_4";
					}
				}				
				link.l5 = "Yelkenlerini indirmen emrini hiçe saydın ve güç kullanarak karşı koydun. Bunun bedeli idam olacak. Başçavuşa çoktan talimat verdim.";
				link.l5.go = "PunishmentAction";
				NextDiag.TempNode = "second time"; 
			}	
		break;
		
		case "offender":
			dialog.text = "Suçlu mu? Benimle dalga mı geçiyorsun,"+GetAddress_Form(NPChar)+"!";
			link.l1 = "Şaka yapmıyorsun. Sen bir korsansın.";
			link.l1.go = "exit";
		break;
		
		case "free_to_officer":
			if ((GetSummonSkillFromName(pchar, "Leadership") + 20) <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = "Senin emrinde hizmet etmek mi? Onun yerine köpekbalıklarını beslerim!";
				link.l1 = "Diline dikkat et yoksa onları beslersin.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Subayınız olmak için, "+GetAddress_Form(NPChar)+"? Katılıyorum. İşimi biliyorum ve kaybedecek hiçbir şeyim yok.";
				link.l1 = "Anlaştık! Git ve işini yap.";
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Bir dakika, fikrimi değiştirdim.";
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_trader":
			if (GetSummonSkillFromName(pchar, "Leadership") <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = LinkRandPhrase("Teklif cazip... ama prensip gereği reddetmek zorundayım.","Üzgünüm, ama arkadaşlarıma yaptıklarından sonra... Bu imkânsız.","Hayır, kaptan. Bunca dehşetten sonra bu işi artık yapamam. Kutsal Meryem dualarımı duyup bana özgürlüğümü verirse, bir daha denize açılmayacağıma yemin ettim.");
				link.l1 = "Karar senin. Israr etmeyeceğim.";	
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Neden olmasın? Ben zavallı bir kaptanım, gemimi kaybettim, karada bana kalan hiçbir şey yok. Sadece borçlar ve faturalar...";
				link.l1 = "Anlaştık! Marangozbaşıya git ve hakkını al. Gemimde sana birazdan bir görev vereceğim.";	
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Biraz bekle, fikrimi değiştirdim.";
				link.l2.go = "exit";
			}
		break;
		
		case "free_to_officer_Hire":
            NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
            NPChar.greeting = "Gr_Officer";
            NPChar.loyality = 5 + rand(10);
		    if (sti(NPChar.reputation) > 41)
		    {
		        NPChar.alignment = "good";
		    }
		    else
		    {
		        NPChar.alignment = "bad";
		    }
            ReleasePrisoner(NPChar); // освободили пленника
            DeleteAttribute(NPChar, "LifeDay") // постоянный
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			// тут трем накопивщиеся сабли и корабли 290704 BOAL -->
			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
            DeleteAttribute(Npchar, "Fellows"); // его офицеры
            Npchar.Fellows.Passengers.id0 = Npchar.index; // свой пассажир

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1";
            
			if(CheckAttribute(NPChar,"Hold_GenQuest")) DeleteAttribute(NPChar, "Hold_GenQuest");
			
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
        break;
				
		case "Slave_1":
			dialog.text = "Ama "+GetAddress_Form(NPChar)+", bunu yapamazsın! Teslim oldum.";
            link.l1 = "Çeneni kapa! ... Onu bağlayın.";
			link.l1.go = "Slave_2";
			link.l99 = "Pekala. Ben karar verene kadar burada kal...";
			link.l99.go = "exit";
		break;
		
		case "Slave_2":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
            if (rand(5) == 1)
            {
    			dialog.text = "Olmaz! Köle olacağıma ölürüm daha iyi!";
                link.l1 = "Yeter artık! Bu bir emirdir!... Başçavuş! Yükleri temizle...";
    			link.l1.go = "free_in_sea_4";
			}			
			else
			{
                if (rand(1) == 1)
                {
                    if (GetPrisonerQty() > 1)
                    {
                        dialog.text = "Kasap! Arkadaşlar, bana katılın, kaybedecek hiçbir şeyimiz yok!";
                        link.l1 = "Yanlış seçim yaptınız, hanımlar. İsyanlarla bizzat ben ilgilenirim, hem de çok hızlı...";
            			link.l1.go = "free_in_sea_battle_all";
                    }
					else
					{
						dialog.text = "Olmaz! Savaşta ölmeyi tercih ederim!";
						link.l1 = "Nasıl istersen...";
						link.l1.go = "free_in_sea_battle_1";
					}	
    			}
    			else
    			{
					dialog.text = "Ah, katılıyorum. Başka seçeneğim yok.";
                    link.l1 = "Harika. Ölü bir kahraman olmaktansa, yaşayan bir köle olmak daha iyidir.";
        			link.l1.go = "Slave_3";				
    			}			
			}
		break;

		case "Slave_3":
            ReleasePrisoner(NPChar); //  пленника в рабы
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", -6);
        	DialogExit();
        	AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
        break;

		case "free_withoutFee":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", gerçekten bu kadar iyi misin, beni fidye istemeden serbest bırakıyor musun?";
            link.l1 = "Evet, benim. Artık özgürsün,"+GetFullName(NPChar);
			link.l1.go = "free_withoutFee_2";
			link.l99 = "Hm... Haklısın! Karar vermek için biraz daha zamana ihtiyacım var.";
			link.l99.go = "exit";
		break;

		case "free_withoutFee_2":
			dialog.text = "Teşekkür ederim, "+GetFullName(PChar)+"! Senin için dua edeceğim.";
            link.l1 = "Şimdi git, ve hayatta kalmaya çalış, yoksa cömertliğim boşa gidecek.";
			link.l1.go = "free_withoutFee_3";
			OfficersReaction("good");
		break;
		
		case "free_withoutFee_3":
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", 2);
        	DialogExit();
        break;	

		case "free_withoutFee_4":	
			switch(NPChar.EncType)
			{
				case "pirate":
					dialog.text = RandPhraseSimple("Teşekkür ederim, kaptan. Ne iyiliğinizi ne de bu günü asla unutmayacağım. Bu işi bırakıp huzurlu limanlarda küçük tekneleri tamir edeceğim. Bunu yapabilirim.","Teşekkür ederim, kaptan! Yemin ederim, bu nankör işi bırakıp balıkçı olacağım.");
					link.l1 = "Eğer dürüstsen sana bol şans dilerim, ama değilsen bir daha karşıma çıkmamayı dua et...";	
				break;
				case "trade":
					dialog.text = "Sana nasıl teşekkür edeceğimi bile bilmiyorum, kaptan. Umudumu çoktan kaybetmiştim. Herkese iyiliğinden bahsedeceğim. Söz veriyorum, senin için bir mum yakacağım! Yeter ki bir kiliseye ulaşayım.";
					link.l1 = "Elveda. Ve bir dahaki sefere, sakın karşı koymayı aklından bile geçirme. Bana ateş edersen, bu senin ve mürettebatının ölüm fermanı olur.";
				break;
				case "war":
					dialog.text = "Teşekkür ederim, kaptan. Sizin için dua edeceğim.";
					link.l1 = "İyi şanslar, ama unutma, eğer peşime düşmeye kalkarsan, sonun olur.";
				break;
			}
			link.l1.go = "free_withoutFee_3";
		break;
		
		case "free_in_sea_battle_1":
            ReleasePrisoner(NPChar); // освободили пленника        	
        	LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
            LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_TmpEnemy);
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, "Prisoner", LAI_GROUP_NEITRAL);
        	DialogExit();
        break;		

		case "free_in_sea_battle_all":
			//ugeen --> привет Сиварду !!! после релиза пленников кол-во пассажиров уменьшается и цикл нихрена дальше не срабатывал
			for(int j = GetPassengersQuantity(pchar) - 1; j > -1; j--)
            {
                cn = GetPassenger(pchar, j);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if (CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                        	ReleasePrisoner(offref); // освободили пленника
							LAi_SetWarriorType(offref);
							LAi_warrior_DialogEnable(offref, false);
                            LAi_group_MoveCharacter(offref, LAI_GROUP_TmpEnemy);
                        }
                    }
                }
            }
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
        	DialogExit();
        break;
		
		case "free_in_sea_4":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";
	        LAi_KillCharacter(NPChar);
        	DialogExit();
        break;

		case "PunishmentAction":
			dialog.text = "Ama "+GetAddress_Form(NPChar)+", bunu yapamazsın! Teslim oldum.";
			link.l1 = "Adamların gittikten sonra. Onlara ihanet ettin... Başçavuş! Onu alın.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Pekala... Bunu düşünmek için zamana ihtiyacım var. Burada kal.";
			link.l2.go = "exit";
        break;

		case "PunishmentAction1":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			AddCharacterExpToSkill(Pchar, "Leadership", -150);
			if (rand(1) == 1)
            {
                if (GetPrisonerQty() > 1)
                {
                    dialog.text = "Kasap! Arkadaşlar, kaybedecek hiçbir şeyimiz yok!";
                    link.l1 = "Yanlış seçim yaptınız, hanımlar. İsyanlarla bizzat ben ilgilenirim ve bunu çok hızlı yaparım...";
					link.l1.go = "free_in_sea_battle_all";
                }
				else
				{
					dialog.text = "Olmaz! Savaşta ölmeyi tercih ederim!";
					link.l1 = "Nasıl istersen...";
					link.l1.go = "free_in_sea_battle_1";
				}	
    		}
			else
    		{
				dialog.text = "Bari dua etmem için bana biraz zaman ver...";
                link.l1 = "Dua et, istersen.";
        		link.l1.go = "PunishmentAction2";				
    		}						
		break;
		
		case "PunishmentAction2":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";		
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
		break;
		
		case "free_tip_off":
			dialog.text = "Senin gibi birine faydalı olabilecek ilginç bilgilerim var. Ama karşılığında özgürlüğümü garanti edeceğine dair sözünü istiyorum.";
			link.l1 = "Sana nasıl garanti verebilirim ki, teklifini bile bilmiyorum? Bilgilerinin bana bir faydası olacağından şüpheliyim.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Sana sadece söz verebilirim.";
			link.l2.go = "free_tip_off_1";
		break;
		
		case "free_tip_off_0":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			DeleteAttribute(NPChar, "Hold_GenQuest");
			DialogExit();
		break;
		
		case "free_tip_off_1":
			switch(NPChar.EncType)
			{
				case "trade":
					sTmp = "He proposed me a freight but this guy was too greedy and I rejected the offer.";  
				break;
				case "war":
					sTmp = "I have escorted him a few times as a commander of a convoy.";
				break;
				case "pirate":
					sTmp = "I had an idea to rob him once but I have never had a single chance to do that.";
				break;
			}
			dialog.text = "Pekala. Bu bana yeter. Şimdi, doğrudan konuya gelelim, "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" zengin bir tüccarın evidir "+NPChar.Hold_GenQuest.Name+". "+"Servetini   gemisiyle   kazandı '"+NPChar.Hold_GenQuest.ShipName+" satıyor "+GetStrSmallRegister(XI_ConvertString(Goods[sti(NPChar.Hold_GenQuest.Goods)].Name+"Acc"))+" rotasıyla : "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.FromCity)+" - "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.ToCity)+". "+"Çok fazla yükü olduğunda, koruma tutar."+sTmp+" Eminim bu bilgi, tek bir adamın hayatından sizin için çok daha değerli.";
			link.l1 = "Bu bilginin bana faydalı olacağından şüpheliyim. Barışçıl tüccarların peşine düşmem.";	
			link.l1.go = "free_tip_off_0";
			link.l2 = "Bu bilginin bana bir faydası olur mu emin değilim, ama sana söz verdim. Lostromos seni mürettebatıma katacak ve en yakın limanda serbest bırakacak.";
			link.l2.go = "free_tip_off_2";			
		break;
		
		case "free_tip_off_2":
			dialog.text = "Teşekkür ederim, kaptan! Dürüstlüğünüzden hiç şüphem yoktu!";
			link.l1 = RandPhraseSimple(RandPhraseSimple("Keşke senin için de aynı şeyi söyleyebilseydim","Üzgünüm, ama senin için aynı şeyi söyleyemem."),RandPhraseSimple("Git, ve unutma ki bir dahaki sefere bu kadar cömert olmayacağım.","Git ve yolumdan çekil. Bir dahaki sefere sana bu kadar kolay inanmayacağım."));
			link.l1.go = "free_tip_off_3";
		break;
		
		case "free_tip_off_3":
			pchar.GenQuest.Hold_GenQuest.Goods 			= NPChar.Hold_GenQuest.Goods;			
			pchar.GenQuest.Hold_GenQuest.Nation 		= NPChar.Hold_GenQuest.Nation; 
			pchar.GenQuest.Hold_GenQuest.Name 			= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.ToCity 		= NPChar.Hold_GenQuest.ToCity;
			pchar.GenQuest.Hold_GenQuest.FromCity 		= NPChar.Hold_GenQuest.FromCity; 
			pchar.GenQuest.Hold_GenQuest.ShipName 		= NPChar.Hold_GenQuest.ShipName;				
			pchar.GenQuest.Hold_GenQuest.City 			= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.CapName		= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.Island			= GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City); 
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern 	= true;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "1");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Acc"))); 
			AddQuestUserData("HoldQuest", "sCityFrom", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.FromCity));
			AddQuestUserData("HoldQuest", "sCityTo", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.ToCity));
			AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
			
			SetFunctionTimerCondition("Hold_GenQuest_SetMerchant_pre", 0, 0, 1+rand(2), false);
			SetFunctionTimerCondition("Hold_GenQuest_MerchantOver", 0, 0, 30, false);
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();			
		break;
	
		case "free_buyout":
			dialog.text = "Ve sana bir teklifim var. "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" hayatlar, dostum, "+NPChar.Hold_GenQuest.Name+" onun adı. Bir zamanlar birlikte iş yapmıştık."+"Onu orada bul. Eminim sana iyi bir para ödeyecektir. Bana borcu var, onunla kendim ilgileneceğim.";
			link.l1 = "Arkadaşın mı, hı? Görelim bakalım.";	
			link.l1.go = "free_buyout1";
			link.l2 = "İlk limanda fidye alabiliyorsam, neden arkadaşını arayayım ki?";
			link.l2.go = "free_tip_off_0";
		break;
	
		case "free_buyout1":
			LAi_CharacterDisableDialog(NPChar);
			
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.CapId		= NPChar.Id;
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "6");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			DialogExit();
		break;

		case "free_by_hoard":
			dialog.text = "Aslında, güzel bir hazinesi olan bir adamı tanıyorum, ama onu kullanacak cesareti yok.";
			link.l1 = "Ne demek istiyorsun?";
			link.l1.go = "free_by_hoard1";
			link.l2 = "Hikayelerini kendine sakla. Ruhun için endişelenmeye başlasan iyi olur.";
			link.l2.go = "free_tip_off_0";
		break;
		
		case "free_by_hoard1":
			dialog.text = "Sana büyük bir hazineye götüren bir hikaye anlatıyorum. Karşılığında, bir sonraki limanda beni serbest bırakacağına dair sözünü istiyorum.";
			link.l1 = "Seninle ne zaman ve ne yapacağıma kendim karar veririm. 'Hikayelerin' hiçbir şeyi değiştirmez.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Dinliyorum. Söz veriyorum.";
			link.l2.go = "free_by_hoard2";
		break;
		
		case "free_by_hoard2":
			dialog.text = "Böylesine onurlu birine güveniyorum "+GetSexPhrase("adam","kadın")+". Sizin gibi insanlar her zaman sözünü tutar! Dünya yansa da, siz sözünüzden dönmezsiniz! Doğru mu, kaptan?";
			link.l1 = "Hikayeni anlat, yoksa seni şimdi bırakırım... denize, hem de kafasız olarak.";
			link.l1.go = "free_by_hoard4";
		break;
		
		case "free_by_hoard4":
			dialog.text = "Ha-ha, güzel şaka... Şimdi dinle. Şurada bir adam var "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" named "+NPChar.Hold_GenQuest.Name+", gençliğinde oldukça pervasız biriydi. O zamanlar pek çok 'iş' çevirirdi..."+"Bir keresinde meyhanede bana bir grubun üyesi olduğunu söylemişti "+GetName(NAMETYPE_VIP,NPChar.Hold_GenQuest.PirateName,NAME_ACC)+" çetesini ve o korsanların bir hazine gömdüğünü gördü."+" O hazine için beş arkadaşının ölümüne sebep oldu... Onun yakalanıp asıldığına dair söylentiler vardı, ama gerçekte işlerden elini çekip bir aile kurdu. Hazinenin yerini hatırlıyordu, hatta bir harita bile çizmişti. Hazinenin peşine birlikte düşmemi teklif etti bana. Batıl inançlı bir adamdı, hazinenin lanetli olduğuna inanıyordu, bu yüzden oraya tek başına gitmekten korkuyordu. Kabul ediyorum, ben de aynı sebepten cesaret edemedim. "+"Haritayı satmaya hazırdı, ama nasıl olsa oraya hiç gitmeyeceğim için neden bana lazım olsun ki...\nİşte benim hikayem bu... Senin gibi cesur birinin işine yarayacağını düşünüyorum, hem harita da oldukça ucuz bu arada.";
			link.l1 = "Ve gerçekten buna inanmamı mı bekliyorsun? Anlattığın hikaye gerçek değil, bu yüzden anlaşmamızı bozuyorum.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "İlginç bir hikaye, gerçi pek inandığım söylenemez. Ama sana söz veriyorum, git ve lostromoya söyle, sana bir ranza versin. Serbestsin.";
			link.l2.go = "free_by_hoard5";
		break;
		
		case "free_by_hoard5":
			dialog.text = "Teşekkür ederim, kaptan! Şimdi bir insanın sözünün değerini anlıyorum "+GetSexPhrase("beyefendi!","hanımefendi!");
			link.l1 = "Git ve yolumdan çekil. Bir dahaki sefere seni bu kadar kolay bırakmam.");
			link.l1.go = "free_by_hoard6";
		break;
		
		case "free_by_hoard6":
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.PirateName	= NPChar.Hold_GenQuest.PirateName;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1) + 2;
			pchar.GenQuest.Hold_GenQuest.Sum		= 10000 + rand(10000);
			pchar.GenQuest.Hold_GenQuest.Treasure	= rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "12");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();					
		break;
		
		case "free_in_sea":
			dialog.text = "Ama, "+GetAddress_Form(NPChar)+", açık denizdeyiz! Bu, beni idam etmiş olmandan farksız!";
			link.l1 = "İstediğin buydu. Elveda. Lostromos emrimi yerine getirecek.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Pekala, henüz karar vermedim.";
			link.l2.go = "exit";
		break;		
		
		//--> Jason, Ложный след
		case "FalseTrace_Prisoner":
			dialog.text = "Katerine! Gerçekten seni buraya gelmen için mi gönderdi? Ne harika bir kız...";
			link.l1 = "Şiiri bir kenara bırakalım, kaptan, ve daha ciddi konulara geçelim. Sana mevcut durumu anlatacağım ve senden bir cevap bekliyorum. Vereceğin cevap hem senin hem de Katerine'in kaderini belirleyecek.";
			link.l1.go = "FalseTrace_Prisoner_1";
		break;
		
		case "FalseTrace_Prisoner_1":
			dialog.text = "Dinliyorum, kaptan.";
			link.l1 = "Senin fluytuna bindim çünkü Katerin'in kocası Adam Rayner, geminde çok miktarda gümüş olduğunu söyledi. Bu numara sayesinde, bir zamanlar ona ait olan ve senden kaçarak ona sığınan bir kadını geri alabildi.";
			link.l1.go = "FalseTrace_Prisoner_2";
		break;
		
		case "FalseTrace_Prisoner_2":
			dialog.text = "Adam mı? O alçak mı? Her şey onun planıydı! Şimdi anlıyorum... Evet, üç ay önce Katrine'in kaçmasına ben yardım ettim. Zavallı kız, ona nasıl davrandığını bir bilsen...";
			link.l1 = "O onun karısıydı ve başına ne geldiği umurumda değil, bu beni ilgilendirmez. Sizin fluyt geminize çıkmakla hata ettim ama artık konuşmak için çok geç. Adam bana yardımım için ödeme yapacağına söz verdi.";
			link.l1.go = "FalseTrace_Prisoner_3";
		break;
		
		case "FalseTrace_Prisoner_3":
			dialog.text = "Adam söz mü verdi? Ha-ha! Ve sen ona inandın mı? Kaptan, onun ne tür biri olduğunu biliyor musun? O...";
			link.l1 = "Katerine bana ondan çokça bahsetti ve bunun için gerçekten uğraştı. Ama onun teklifi mantıklı geliyor ve bu herifin sözüne güvenmek için bir sebebim olmasa da, belki bu sefer doğruyu söylüyordur. O yüzden lafı fazla uzatmadan sadede gelelim...";
			link.l1.go = "FalseTrace_Prisoner_4";
		break;
		
		case "FalseTrace_Prisoner_4":
			dialog.text = "";
			link.l1 = "Seni yetkililere fidye karşılığında teslim edecektim ve Adam ile Katerine'i de teslim edecektim "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Acc")+", then get from Adam the information about Squint-Eyed Solly's gold and sail to it. But Katerine persuaded me to speak with you first; she said you might offer me something better and more reliable than Adam did, in exchange for your lives and freedom.";
			link.l1.go = "FalseTrace_Prisoner_5";
		break;
		
		case "FalseTrace_Prisoner_5":
			dialog.text = "";
			link.l1 = "İşte bu yüzden burada durup seninle konuşuyorum. Ben anlattım. Şimdi sıra sende. Benim ve Katerine'in söylediklerini düşün, bana fikrini söyle. Fazla vaktin yok.";
			link.l1.go = "FalseTrace_Prisoner_6";
		break;
		
		case "FalseTrace_Prisoner_6":
			dialog.text = "Kaptan! İyi bir adam olduğunu düşünmesem de, zavallı bir kızın yalvarışlarını dinledin ve buraya geldin. Bu bana onurlu olabileceğini ve merhamet duyabileceğini gösteriyor. Zamana ihtiyacım yok, sana teklifimi sunmaya hazırım.";
			link.l1 = "Gerçekten mi? Harika! O halde, dinliyorum.";
			link.l1.go = "FalseTrace_Prisoner_7";
		break;
		
		case "FalseTrace_Prisoner_7":
			dialog.text = "Adam Rayner’ı tutuklayıp zincire vuracaksın. Sonra beni ve Katherine’i alıp "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". Şehre yanaşma, sonuçta benim fluyt'umu batıran sendin, üçünüzü de şurada bırak "+XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen")+"\nI would also ask you for a weapon. We will go to the city through the jungle, and I'll make sure that the scum pays not only for his crimes but for yours as well. He deserves it\nYou have my word that your name won't come up. In return, I will give you true information concerning a ship carrying the gold of an enemy state\nIt won't be a great challenge for you, but it does have teeth; you will gain a fine booty. Much better than my ransom and the so-called Squint-Eyed Solly's treasures. Do we have a deal?";
			link.l1 = "Senin planını beğenmiyorum. Bence buradan ayrılır ayrılmaz yerel yetkililer peşime düşecek."+XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen")+". Hayır kaptan, boynumu riske atmayacağım. Konuşmamız burada bitti.";
			link.l1.go = "FalseTrace_Prisoner_8";
			link.l2 = "Görünüşe bakılırsa Katerine haklıymış. Teklifini beğendim. Adam Rayner tutuklanacak. Hemen halledeceğim. Adam'ı yakaladıktan sonra seni serbest bırakacağız. Görüşürüz, kaptan!";
			link.l2.go = "FalseTrace_Prisoner_9";
		break;
		
		case "FalseTrace_Prisoner_8":
			DialogExit();
			AddQuestRecord("FalseTrace", "9");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			bQuestDisableMapEnter = false;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_Prisoner_9":
			DialogExit();
			AddQuestRecord("FalseTrace", "10");
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			AddDialogExitQuestFunction("SetCheckForGoldShip");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FalseTrace.PrisonerID = npchar.id;
			Pchar.questTemp.FalseTrace.PrisonerIDX = GetCharacterIndex(npchar.id);
		break;
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "Buraya vaaz vermeye mi geldin, yoksa iş yapmaya mı?";
			link.l1 = "Bir işim var. Suç ortağın Bertrand Pinette'i arıyorum. Onun yüzünden başım büyük belada. Nerede bulabilirim onu, ha?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Neden sana bunu söyleyeceğimi düşünüyorsun?";
			link.l1 = "Hayatın tehlikede. Seni Basse-Terre’e götürüp valiye teslim edeceğim ve Carlos de Milyar’ın kaçmasına yardım eden bir firarinin yakalanması için konan ödülü alacağım. Seçim senin. Ya bana Pinette’in nerede olduğunu söylersin, ya da ikimiz de Guadeloupe’a gideriz.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "Demek her şeyi biliyorsun... Peki, sana Bertrand Pinette hakkında bildiğim her şeyi anlatacağım, ama karşılığında beni serbest bırakmalısın.";
			link.l1 = "Devam et, anlat bakalım. Seni yine Mosquito Körfezi'ne bırakacağım, tıpkı geçen sefer olduğu gibi. Ama bana yalan söylersen, geri dönerim ve Don Carlos'un sana hediye ettiği o plantasyonu ateşe veririm. Ayrıca yerini Basse-Terre'e de bildiririm, böylece peşine düşen tek kişi ben olmam.";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "Önce beni oraya çıkar. Böylece kendimi daha güvende hissederim, yemin ederim sana her şeyi anlatacağım.";
			link.l1 = "Pekâlâ. Zaten bir yere gidecek değilsin.";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "16");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FMQG.PrisonerID = npchar.id;
			Pchar.questTemp.FMQG.PrisonerIDX = GetCharacterIndex(npchar.id);
			pchar.quest.FMQG_SailMoskitos.win_condition.l1 = "location";
			pchar.quest.FMQG_SailMoskitos.win_condition.l1.location = "Shore47";
			pchar.quest.FMQG_SailMoskitos.function = "FMQG_ArriveMoskitos";
			pchar.questTemp.FMQG = "to_moskitos";
			AddMapQuestMarkShore("Shore47", true);
			bDisableMapEnter = false; // Rebbebion, теперь можно
		break;
		
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
	}
}
