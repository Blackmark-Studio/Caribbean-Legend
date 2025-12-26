void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;
	ref rColony;
	
	int iTest;
	
	bool  ok; // лесник . спецпеременная.

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	iTest = FindColony(NPChar.City);
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_GoOut":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			DoQuestFunctionDelay("HouseEnc_TimerGoUot", 10.0);
			pchar.questTemp.HouseEncTimer = pchar.location;
			pchar.questTemp.HouseEncTimer.Id = npchar.id;
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_close":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------------- мужик ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Kasabada alarm verilmiş. Görünen o ki, artık benim de silaha sarılma vaktim geldi...","Şehir muhafızları peşinden koşmuyor mu, yoksa? ","Burada sığınacak bir yer bulamazsın, ama kaburgalarının arasında birkaç santim soğuk çelik bulabilirsin!"),LinkRandPhrase("Ne istiyorsun?"+GetSexPhrase("serseri","serseri")+"?! Şehir muhafızları çoktan senin izini sürdü, fazla uzağa gidemezsin, "+GetSexPhrase("pis korsan","sen korsan kadın")+"!","Pis katil! Muhafızlar!!!","Senden korkmuyorum, "+GetSexPhrase("sürüngen","kadın")+"! Yakında kalemizde asılacaksın, fazla uzağa gidemezsin..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Yaşamaktan bıktığını görüyorum...","Öyle görünüyor ki,  sakin bir hayat  bu şehrin insanlarına nasip olmuyor "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Cehenneme git!","Heh,   bunlar hayatının son birkaç saniyesi olacak..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "Seni uyardım. Şimdi belaya bulaşmak isteyip istemediğine kendin karar verebilirsin.";
					link.l1 = "Heh!";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Evimde ne işin var, alçak herif?! Buradan defolup gitmek için on saniyen var!";
					link.l1 = LinkRandPhrase("Heh, demek burada da beni tanıyorlar!","Şöhretim benden bir adım önde gitmiş...","Hmm, anladım.");
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("Sizi evimde ağırlamaktan memnuniyet duyarım. Benimle bir işiniz mi var?","Sana nasıl yardımcı olabilirim?","Hmm... Size nasıl yardımcı olabilirim?","Üzgünüm, ama eğer benimle bir işiniz yoksa, lütfen beni rahatsız etmeyin...","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Hayır, sadece etrafa bakıyorum, yeni insanlarla tanışıyorum...","Hayır, özellikle bir şey yok...","Hiçbir şey...","Peki, dediğiniz gibi olsun.",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("Üzgünüm, ama gece ziyaret için en uygun zaman değil, bu yüzden sizi hemen evimden ayrılmaya davet etmek zorundayım!","Zaten söyledim, geç oldu. Lütfen, gidin.","Kaba görünmek istemem, ama derhal evimden çıkmanızı rica ediyorum!","Lanet olsun, neler oluyor?! Muhafızlar! Hırsızlar!","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Pekala, anladım...","Evet, bir dakika...","Pekâlâ, ama bu kadar heyecanlanma.","Hangi hırsızlar?! Kapa çeneni!",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = "Ah, kendimi tanıtmama izin verin - "+GetFullName(npchar)+". Sizi misafirimiz olarak ağırlamaktan büyük mutluluk duyuyoruz. Bu kasabada misafirperverlik yasalarına saygı gösterilir.";
			link.l1 = GetFullName(pchar)+", lütfen...";
			link.l1.go = "exit_setOwner";
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Sen "+GetSexPhrase("Bir hırsız, görüyorum! Muhafızlar, yakalayın onu","Bir hırsız, demek! Muhafızlar, yakalayın onu")+"!!!","İnanamıyorum! Bir saniyeliğine arkamı döndüm – ve sen eşyalarımı karıştırıyorsun! Dur, hırsız!!!","Gardiyanlar! Soygun! Hırsızı durdurun!!!");
			link.l1 = "Aaaah, şeytan!!!";
			link.l1.go = "fight";
		break;
		// --------------------------------- баба ---------------------------------
		case "HouseWoman":
			NextDiag.TempNode = "HouseWoman";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Seni uyarıyorum, kocam yakında dönecek! Evimden hemen çıksan iyi olur!","Kaçamayacağını sanıyorum! Ayrıca kocamın yakında eve döneceğini unutma!","Kocam yakında evde olacak! Hemen gitmelisiniz!"),LinkRandPhrase("Kocamın evde olmaması ne yazık... Defol! Hemen!!!","Pis katil, hemen evimden defol! Muhafızlar!",""+GetSexPhrase("Ne alçak adam","Ne pislik")+"... Yakında kocam dönecek ve kanının ne renk olduğunu görecek!"));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Ah, kocanız... ooooh... titriyorum...","Heh... Biliyor musun, kızım, kocan sadece bir adam... ayaklarının dibinde ölü görmek istemezsin herhalde, değil mi?"),RandPhraseSimple("Kapa çeneni, kadın, yoksa karnını deşerim...","Ben burada istediğim kadar kalacağım. Ve sen de aklın varsa çeneni kapalı tutarsın..."));
				link.l1.go = "exit_setOwner";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "Seni uyardım. Çık git yoksa pişman olacaksın!";
					link.l1 = "Ne aptal bir kadın...";
					link.l1.go = "exit";
				}
				else
				{					
					dialog.text = "Benim evimde ne yapıyorsun, "+GetSexPhrase("alçak","serseri")+"?! Eğer on saniye içinde gitmezsen, muhafızları çağıracağım!";
					link.l1 = "Ne aptal bir kadın...";
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("Sizi evimizde görmekten memnun oldum. Benim adım "+GetFullName(npchar)+". Size nasıl yardımcı olabilirim?","Hâlâ burada mısın?","Hm, affedersiniz, ama artık gitme vaktiniz gelmedi mi?","Misafirperverliğimizi suistimal etmemenizi rica ederim.","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(GetFullName(pchar)+" hizmetinizdeyim. Buraya özel bir sebep olmadan geldim, sadece sizinle tanışmak istedim.","Hâlâ buradasın.","Yani, bilmiyorum...","Pekala.",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseWoman_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("Aman Tanrım, böyle bir saatte evime neden giriyorsun! Beni gerçekten çok korkuttun... Lütfen, yarın gel bizi ziyaret et!","Lütfen, evimizi terk edin!"+GetSexPhrase("","Ben evli bir kadınım!")+"","Son kez evimizi terk etmeni istiyorum!","Burada neler oluyor?!","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Korkma, sana zarar vermeyeceğim.","Pekâlâ, sadece bu kadar telaşlanma.","Gidiyorum.","Ne var ne yok?",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "HouseWoman_2", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseWoman_1":
			dialog.text = "Misafirlerimiz her zaman başımızın tacıdır. Ama burada fazla oyalanmayın,"+GetSexPhrase(", çünkü evli bir kadınım..."," çünkü yapacak çok işim var...")+"";
			link.l1 = "Ah, evet, tabii...";
			link.l1.go = "exit_setOwner";
		break;
		case "Woman_FackYou":
			dialog.text = "Demek öyle mi? Seni misafirim olarak ağırladım, sen ise sandıklarımızı karıştırıyorsun?! Muhafızlar!";
			link.l1 = "Kapa çeneni, kaltak!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		case "HouseWoman_2":
			dialog.text = "Sana evimizi kibarca terk etmeni söyledim, ama beni dinlemedin! Yeter! Yardım edin! Muhafızlar!";
			link.l1 = "Kes sesini, aptal kadın! Deli misin?!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break; 
		//--------------------------------- завсклад ---------------------------------		
		case "SkladMan":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Kasabada alarm verilmiş. Görünüşe bakılırsa, silaha sarılma zamanı benim için de geldi...","Şehir muhafızları peşinden koşmuyor mu, yoksa? ","Burada sığınacak bir yer bulamazsın, ama kaburgalarının arasında birkaç santim soğuk çelik bulabilirsin!"),LinkRandPhrase("Ne istiyorsun?"+GetSexPhrase("alçak","serseri")+"?! Şehir muhafızları senin kokunu çoktan aldı, fazla uzağa gidemezsin, "+GetSexPhrase("pislik korsan","fahişe")+"!","Pis katil! Muhafızlar!!!","Senden korkmuyorum, "+GetSexPhrase("serseri","fahişe")+"! Yakında kalemizde asılacaksın, fazla uzağa gidemezsin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Yaşamaktan bıkmış gibisin...","Görünüşe göre,  için vatandaşlara huzurlu bir hayat yok."+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Cehenneme git!","Heh,   bunlar hayatının son birkaç saniyesi olacak..."));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
				dialog.text = NPCStringReactionRepeat("Hoş geldiniz! Benim adım "+GetFullName(npchar)+". Burada ben sorumluyum, o yüzden yanında bir şey götürmeyi aklından bile geçirme...","Kendine dikkat et ve aklında bulunsun, seni gözümden kaçırmıyorum.","Sandıkları karıştırmadığın sürece burada kalabilirsin. Zaten yalnız başıma sıkılıyorum...",RandPhraseSimple("Aman Tanrım, çok sıkıldım!","Kahretsin, ne yapmalıyım? Burada olmak çok sıkıcı!"),"block",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Pekala, endişelenme.","Tabii ki!","Anladım...","Evet, bu kulağa sorun gibi geliyor.",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
		break;
		
		case "SkladMan1":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Kasabada alarm verilmiş. Görünüşe bakılırsa, benim de silaha sarılma vaktim geldi...","Şehir muhafızları peşinden koşmuyor mu, yoksa? ","Burada sana barınacak bir yer yok, ama kaburgalarının arasında birkaç santim soğuk çelik bulabilirsin!"),LinkRandPhrase("Ne istiyorsun?"+GetSexPhrase("serseri","serseri")+"?! Şehir muhafızları senin kokunu çoktan aldı, fazla uzağa gidemezsin, "+GetSexPhrase("pis korsan","kadın")+"!",""+GetSexPhrase("Pis","Pis")+" Katil! Muhafızlar!!!","Senden korkmuyorum, "+GetSexPhrase("sürüngen","fahişe")+"! Yakında kalemizde asılacaksın, fazla uzağa gidemezsin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Yaşamaktan bıktın galiba...","Öyle görünüyor ki,  sakin bir hayat  bu şehrin insanlarına nasip olmuyor "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Cehenneme git!","Heh,   bunlar   hayatının   son   birkaç   saniyesi   olacak..."));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			dialog.text = NPCStringReactionRepeat("Burada ben sorumluyum, o yüzden yanında bir şey götürmeyi aklından bile geçirme...","Kendine dikkat et ve seni gözümden kaçırmadığımı unutma.","Sandıkları karıştırmadığın sürece burada kalabilirsin. Zaten yalnız başıma sıkılıyorum...",RandPhraseSimple("Aman Tanrım, çok sıkıldım!","Lanet olsun, ne yapmalıyım? Burada olmak çok sıkıcı!"),"block",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Pekala, endişelenme.","Tabii!","Anladım...","Evet, bu gerçekten bir sorun gibi görünüyor.",npchar,Dialog.CurrentNode);	
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
			//открывание двери верфи по квесту промышленного шпионажа
			if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && pchar.questTemp.different.ShipyardsMap == "toTarget" && npchar.city == pchar.questTemp.different.ShipyardsMap.city && locations[reload_cur_location_index].type == "shipyard")
			{
				link.l2 = "Dinle dostum, seninle açıkça konuşmak istiyorum.";
				link.l2.go = "ShipyardsMap_1";
				pchar.questTemp.different.ShipyardsMap = "toResult";					
			}
			// ugeen --> склад товаров для ГГ				
			if(CheckAttribute(NPChar,"Storage"))
			{
				if(!CheckAttribute(NPChar, "Storage.Speak"))
				{
					dialog.text = "Sana cazip bir teklifim var. Belki ilgini çekebilir.";
					link.l7 = "Gerçekten mi? Peki, dinliyorum.";
					link.l7.go = "storage_rent";
				}
				else
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Beni depoya götür. Ne durumda olduğunu görmek istiyorum.";
						link.l7.go = "storage_0";
						link.l8 = "Depoyu boşaltmaya karar verdim. Artık ona ihtiyacım yok.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "Bir depodan bahsettiniz. Hâlâ boş mu?";
							link.l7.go = "storage_01";
						}						
					}
				}		
			// <-- ugeen
			}		
		break;
		
		//--------------------------------- Аренда склада ---------------------------------
		case "storage_rent":
			NPChar.Storage.Speak = true;
			dialog.text = "Depo olarak kullanmaya uygun bir alanımız var. Makul bir fiyata kiralamak ister misiniz? Bir düşünsenize, değerli yüklerinizi saklayabileceğiniz kendi deponuz olurdu...";
			link.l1 = "Bir depo, diyorsun? Evet, gerçekten cazip... Peki, yeterince büyük mü? Ve kirası ne kadar olacak?";
			link.l1.go = "storage_rent1";
		break;
		
		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Burası oldukça geniş, bir liman deposu için bile. Bakalım... 50.000 kentner yük alabilir. "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+"  ayda bir, mallarınızı güvenle saklayabilirim. "+"Bu, adamlarımla birlikte onu korumayı, su baskınından muhafaza etmeyi ve farelerle savaşmayı da kapsıyor. Ne dersin? Ha, bir de gizlilik var tabii, o zaten kendiliğinden anlaşılır.";
			link.l1 = "Tabii. Ona bir bakabilir miyim?";	
			link.l1.go = "storage_rent2";
			link.l2 = "Bu çok fazla. Hem de eminim orası su basmış ve fare kaynıyordur.";
			link.l2.go = "storage_rent3";		
		break;
		
		case "storage_rent2":
			dialog.text = "Tabii, tabii. Ama... bir aylık ücreti peşin almam gerekecek. ";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Sen... gerçekten iyi bir tüccarsın, söylemeliyim. Al paranı ... bu kulübeyi kiralıyorum.";
				link.l1.go = "storage_11";
			}
			else
			{	
				link.l1 = "Sen... oldukça ticari birisin, söylemeliyim. Peki, parayı getireceğim.";
				link.l1.go = "exit";
			}	
		break;
		
		case "storage_rent3":
			dialog.text = "Dediğiniz gibi. Fikriniz değişirse, bana haber verin yeter. Ayrıca böyle güzel bir ambarın uzun süre boş kalmayacağını unutmayın...";
			link.l1 = " Sorun değil. İhtiyacım olursa sana haber veririm. ";
			link.l1.go = "exit";
		break;
		
		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "Ve kiraya gelince, hâlâ bana borcun var  "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "Pekala, şimdi kiranı ödeyeceğim.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "Daha sonra geri geleceğim.";
					link.l1.go = "exit";
				}
			}		
			else
			{ // лесник . если забыл с собой корабль то никак.
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "Devam et.";
				link.l1 = "Teşekkürler.";
				link.l1.go = "storage_2";
				}
				else
				{
                dialog.text = RandPhraseSimple("Kaptan, geminiz nerede? Yükü nasıl taşımayı düşünüyorsunuz?","Liman’da gemini göremiyorum. Onu tam olarak nasıl yükleyeceksin?");
                link.l1 = RandPhraseSimple("Ah... Bunu tamamen unutmuşum!","Lanet olsun, doğru!");
			    link.l1.go = "exit";
				break;
                }			
			}
			link.l2 = "Hayır, fikrimi değiştirdim.";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			dialog.text = "Hayır, "+GetSexPhrase("bayım","hanımefendi")+", hâlâ boş ve seni bekliyor. Sonunda teklifimi geri çevirmeyeceğini biliyordum.";
			link.l1 = "Çok iyi. Kiralayacağım.";
			link.l1.go = "storage_1";
			link.l2 = "Hayır, sadece aklıma geldi...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Hatırlayacağın gibi, bir aylık ödemeyi peşin almam gerekiyor.";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Tabii ki, hatırlıyorum. Buyurun.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Kahretsin. Peki, parayı getireceğim.";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_Set("ach_67"); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "Şimdiden gidiyor musunuz? Ne yazık, burası gerçekten harika bir yer ve şartları da çok iyi. Emin olun, Karayipler'de böyle bir fırsatı başka hiçbir yerde bulamazsınız.";
			link.l1 = "Söyledim, orayı boşaltıyorum. Yoksa havayı depolamak için de mi ödeme yapmamı istiyorsunuz? Başka bir kiracı arayabilirsiniz.";
			link.l1.go = "storage_4";
			link.l2 = "Karayipler'de hiçbir yerde yok diyorsun? Peki, o zaman bir süreliğine elimde tutarım. Ama şunu söylemeliyim, kirası biraz fazla yüksek.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "Ve kiraya gelince, bana hâlâ borcun var "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "Pekala.";
					link.l1.go = "storage_5";
				}
			}
			else
			{ // лесник . если нет корабля то и товар не забрать
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "Eşyalarını topla, ben de depoyu kapatacağım.";
				link.l1 = "Pekala.";
				link.l1.go = "storage_6";
				}
				else
				{
                dialog.text = RandPhraseSimple("Kaptan, geminiz nerede? Yükü nasıl taşımayı düşünüyorsunuz?","Liman’da gemini göremiyorum. Onu tam olarak nasıl yükleyeceksin?");
                link.l1 = RandPhraseSimple("Ah... Bunu tamamen unuttum!","Kahretsin, doğru ya!");
			    link.l1.go = "exit";
				break;
                }				
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		//--------------------------------- Аренда склада ---------------------------------
		
		case "ShipyardsMap_1":
			dialog.text = "Heh! Tamam, konuşalım.";
			link.l1 = "Gece, etrafta kimse yokken tersaneye gitmem lazım.";
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			if (sti(pchar.questTemp.different.ShipyardsMap.skladFight))
			{
				dialog.text = "Sana bak hele! Hey, muhafızlar, burada bir hırsız var!!!";
				link.l1 = "Hangi hırsız? Ben sadece konuşmak istemiştim!";
				link.l1.go = "fight";
				AddCharacterExpToSkill(pchar, "FencingL", 5);
				AddCharacterExpToSkill(pchar, "FencingS", 5);
				AddCharacterExpToSkill(pchar, "FencingH", 5);
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
				dialog.text = "Vay canına! Şuna bak, "+GetSexPhrase("dostum","kız")+" . Böyle bir istekle tersane deposuna gelmek!";
				link.l1 = "Tersaneye kendim gitmem gerekiyor. Senin ambarın umurumda bile değil.";
				link.l1.go = "ShipyardsMap_3";
				AddCharacterExpToSkill(pchar, "Fortune", 10);
			}
		break;
		case "ShipyardsMap_3":
			dialog.text = "Ama neden buna ihtiyacın var?";
			link.l1 = "Bir ihtiyaç var. Ve bunun için ödeme yapmaya hazırım...";
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = "Hmm, bu daha iyi... Pekala! Hadi ver bakalım "+FindRussianMoneyString(sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000)+", ve ertesi gün tersanenin kapısını açık bırakacağım.";
			link.l1 = "Bu çok pahalı. O zaman onsuz idare edeceğim...";
			link.l1.go = "exit";
			if (sti(pchar.money) >= (sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000))
			{
				link.l2 = "Pekala, kabul ediyorum. Al paranı ve anlaştığımız gibi yap.";
				link.l2.go = "ShipyardsMap_5";
			}
		break;
		case "ShipyardsMap_5":
			dialog.text = "Merak etme, halledilecek.";
			link.l1 = "Umarım öyle olur...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000);
			AddQuestRecord("ShipyardsMap", "5");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			//снимаем close_for_night
			string  sName;
			int location_index = FindLocation(npchar.city + "_town");
    		makearef(arRld, Locations[location_index].reload);
    		Qty = GetAttributesNum(arRld);
    		for (int a=0; a<Qty; a++)
    		{
    			arDis = GetAttributeN(arRld, a);
				sName = arDis.go;
    			if (findsubstr(sName, "_shipyard" , 0) != -1)
    			{
					DeleteAttribute(arDis, "close_for_night");
					break;
    			}
    		}
			LocatorReloadEnterDisable(npchar.city + "_shipyard", "reload2", true);
			//ставим таймер на возврат close_for_night
			SetTimerFunction("ShipyardsMap_returnCFN", 0, 0, 2);
		break;

	}
}
