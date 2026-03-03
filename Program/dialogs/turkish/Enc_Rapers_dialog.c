void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "Exit_Fight":	
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar); 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			
			if(pchar.GenQuest.EncGirl == "RapersTreasure")
			{
				LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
			}			
			else
			{
				LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");			
				sld = CharacterFromID("CangGirl");
				LAi_SetActorType(sld);
				LAi_ActorAfraid(sld, npchar, true);
			}	
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_RapersBeforeDialog");
			}
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
			DialogExit();	
			AddDialogExitQuest("OpenTheDoors");			
		break;
		
		case "First time":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
//			Diag.TempNode = "OnceAgain";
			if(pchar.GenQuest.EncGirl == "Begin_1")
			{
				dialog.text = LinkRandPhrase("Kendi yoluna git, "+GetSexPhrase("ahbap","kız")+". Sonunda bize teşekkür edecek, biliyorsun.","Defol git! Bırak beyefendiler keyfine baksın.","Bu seni ilgilendirmez, "+GetSexPhrase("yabancı","kız")+". Sadece biraz eğleneceğiz, hepsi bu!");
				link.l1 = LinkRandPhrase("Buna izin vermem!","Kötü planlarından hemen vazgeç!","Herhangi bir şiddete asla tahammül etmeyeceğim!");
				link.l1.go = "Node_Fight";
				link.l2 = RandPhraseSimple("Anladım, gidiyorum. Rahatsız ettiğim için özür dilerim.","Bir daha sizi rahatsız etmeye cesaret edemem. Rahatsız ettiğim için özür dilerim.");
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_11";
			}
			if(pchar.GenQuest.EncGirl == "Begin_2")
			{
				if(sti(pchar.rank) < 10)
				{
					dialog.text = LinkRandPhrase("Kendi yoluna git, "+GetSexPhrase("ahbap","kız")+". Sonunda bize teşekkür edecek, biliyorsun.","Defol! Bırak beyefendiler keyfine baksın.","Bu seni ilgilendirmez, "+GetSexPhrase("yabancı","kız")+". Sadece biraz eğleneceğiz, hepsi bu!!");
					link.l1 = LinkRandPhrase("Buna izin vermeyeceğim!","Kötü planlarından hemen vazgeç!","Herhangi bir şiddete asla tahammül etmeyeceğim!");
					link.l1.go = "Node_Fight";
					link.l2 = RandPhraseSimple("Anladım, gidiyorum. Rahatsız ettiğim için üzgünüm.","Bir daha sizi rahatsız etmeye cesaret edemem. Rahatsız ettiğim için üzgünüm.");
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_11";
				}
				else
				{
					dialog.text = RandPhraseSimple("Hey, "+GetSexPhrase("yabancı","genç hanım")+", neden bela arıyorsun? Bu kız yerleşkemizde 'tanınmış' biridir. Biz ona zaten parasını verdik, ama seni fark etti ve paramızla kaçmaya karar verdi.","Hey, "+GetSexPhrase("dostum","kız")+", kendi yoluna git ve işlerimize karışma. Bu kızı zar oyununda kazandık ama biraz hızlı davrandı ve kaçtı, bir saattir bu ormanda peşindeyiz.");
					link.l1 = "Umurumda değil, ona zarar vermene izin vermeyeceğim!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("Ah, anladım! Az kalsın ona inanacaktım! Ne kadın ama...","Ha, peki, o zaman mesele başka. Neyse, iyi eğlenceler, dostlar!");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}	
			}
			if(pchar.GenQuest.EncGirl == "Begin_3")
			{
				if(sti(pchar.rank) < 20)
				{	
					dialog.text = "Kendi yoluna git, "+GetSexPhrase("iyi adam","genç hanımefendi")+". Sensiz de hallederiz.";
					link.l1 = "Herhangi bir şiddete asla tahammül etmeyeceğim!";
					link.l1.go = "Node_5";
					pchar.GenQuest.EncGirl = "Begin_33";
				}
				else
				{
					dialog.text = RandPhraseSimple("Hey, "+GetSexPhrase("yabancı","genç hanımefendi")+", neden bela arıyorsun? Bu kız yerleşkemizde 'tanınmış' biri. Biz ona zaten parasını ödedik, ama seni fark etti ve paramızla kaçmaya karar verdi.","Hey, "+GetSexPhrase("dostum","kız")+", kendi yoluna git ve bizim işimize karışma. Bu kızı zar oyununda kazandık, ama kaçmakta biraz fazla hızlıydı, bir saattir peşindeyiz.");
					link.l1 = "Umurumda değil - ona zarar vermene izin vermem!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("Ah, anladım! Az kalsın ona inanacaktım! Ne kadın ama...","Ah, peki, o zaman mesele başka. Hadi bakalım, iyi eğlenceler çocuklar!");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}
			}			
		break;
		
		case "Node_Fight":
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Eh, yürüyüş için kesinlikle doğru zamanı seçmişsin...","Demek kahraman olmaya karar verdin?")+" Hallet "+GetSexPhrase("im","er")+", çocuklar!","Sen "+GetSexPhrase("pislik","pislik")+"! Bizim yolumuza çıkmaya cüret mi ediyorsun?! Kes h"+GetSexPhrase("im","er")+"!");
			link.l1 = "Ben daha tehditkâr insanlarla karşılaştım!";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_3":
			pchar.GenQuest.EncGirl.price = 1100*(rand(4)+5) + 200 * sti(pchar.rank);
			dialog.text = "Bilmelisin ki o bize epey pahalıya patladı! Eğer bu kadar asil olduğunu düşünüyorsan, onu alabilirsin "+sti(pchar.GenQuest.EncGirl.price)+" pesos."+GetSexPhrase(" Onunla iyi vakit geçireceksin, he-he...","")+"";
			if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.price))
			{
				link.l1 = RandPhraseSimple("Al paran burada. Onu yanıma alıyorum.","Dişlerini sıkmayı bırak. Kızı yanıma alıyorum. Al paran burada.");
				link.l1.go = "Node_4";
			}	
			link.l2 = LinkRandPhrase("Yani, istediğin para mı? Yoksa soğuk çeliği mi tercih edersin?","Komik mi bu, kıza bak, ahmak! Korkmuş!","Kimi kandırmaya çalışıyorsun, ahlaksız herif!");
			link.l2.go = "Node_Fight";
		break;
		
		case "Node_4": // бандюки уходят, девица остаётся - ГГ ее выкупил у бандюков
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.price))); 
			ChangeCharacterComplexReputation(pchar,"nobility", 7);
			//pchar.quest.LandEnc_RapersBadExit.over = "yes";
			sGlobalTemp = "Saved_CangGirl";
			pchar.GenQuest.EncGirl.Ransom = true;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_5":
			dialog.text = "Öncelikle ona neden inanıyorsun? Hangi şiddet? O evden kaçtı, biz de patronumuz tarafından onu bulmamız için gönderildik.";
			link.l1 = RandPhraseSimple("Pekâlâ, o zaman bu başka bir hikaye. Git, kaçak olanını kovala.","Anladım. O zaman peşinden koşmaya devam et... benim de halletmem gereken işlerim var.");
			link.l1.go = "Exit_NoFight";
			link.l2 = RandPhraseSimple("Bu masalları torunlarına anlatırsın, eğer bir gün onları görecek kadar yaşarsan!","Kimi kandırmaya çalışıyorsun, seni alçak?!");
			link.l2.go = "Node_6";
			link.l3 = "Onu kendim eve götüreceğim, sorun çıkmasın diye. Ebeveynleri kim?";
			link.l3.go = "Node_7";
		break;
		
		case "Node_6":
			dialog.text = "Ölmek mi istiyorsun? Bu senin seçimin...";
			link.l1 = "Konuşan kişiye bak.";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_7":
			sGlobalTemp = "Saved_CangGirl";
			if(pchar.GenQuest.EncGirl.city == "Panama") i = hrand(2);
			else	i = hrand(3);
			switch (i)
			{
				case 0:
					pchar.GenQuest.EncGirl.FatherNom = "is a store owner";
					pchar.GenQuest.EncGirl.FatherGen = "of a store owner";
					pchar.GenQuest.EncGirl.Father = "store_keeper";
				break;
				case 1:
					pchar.GenQuest.EncGirl.FatherNom = "serves in the port office";
					pchar.GenQuest.EncGirl.FatherGen = "who serves in the port office";
					pchar.GenQuest.EncGirl.Father = "portman_keeper";
				break;
				case 2:
					pchar.GenQuest.EncGirl.FatherNom = "serves as the prison's commandant";
					pchar.GenQuest.EncGirl.FatherGen = "of a prison's commandant";
					pchar.GenQuest.EncGirl.Father = "fort_keeper";
				break;
				case 3:
					pchar.GenQuest.EncGirl.FatherNom = "is a shipyard owner";
					pchar.GenQuest.EncGirl.FatherGen = "of a shipyard owner";
					pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
				break;				
			}
			dialog.text = "Babası "+pchar.GenQuest.EncGirl.FatherNom+",   yerleşiminde "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+". Ama lütfen, bizi yüzüstü bırakma, çünkü onunla oyun olmaz, hepimizin derisini yüzer...";
			link.l1 = "Merak etme. Onu ona teslim edeceğim.";
			link.l1.go = "Node_12";
			pchar.GenQuest.EncGirl = "toParents";
		break;
		
		case "Node_12":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, true);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
				sld.lifeDay = 0;
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_8":
			dialog.text = "Ve yine karşılaştık. Arkadaşın nerede? Aslında, sen buradayken ona ihtiyacım yok.";
			link.l1 = "Beyler, bence artık genç kızı rahat bırakmanız için yeterince para aldınız.";
			link.l1.go = "Node_9";
		break;
		
		case "Node_9":
			if(hrand(1) == 0)
			{	
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;	
			}	
			else
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);	
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;	
			}	
			pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			switch(hrand(4))
			{
				case 0:
					sTemp = "a leg";
				break;
				case 1:
					sTemp = "an arm";
				break;
				case 2:
					sTemp = "an ear";
				break;
				case 3:
					sTemp = "a nose";
				break;
				case 4:
					sTemp = "an eye";
				break;
			}
			dialog.text = "Senin paran   buradaki hazinelerle   nasıl kıyaslanabilir ki "+GetName(pchar.GenQuest.EncGirl.PirateIdx,pchar.GenQuest.EncGirl.PirateName1,NAME_GEN)+"? "+"O kadar açgözlüydü ki, sırf fazladan masraf olmasın diye kendi kızını bile evlendirmek istemedi...\nAma bizim payımızı sandıklarında kilitli tutuyor! "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.PirateName2,NAME_NOM)+" güverte savaşında kaybetti "+sTemp+"! Ayrıca, senin elinde ne var peki? "+"Bir avuç zavallı gümüş mü? "+GetName(pchar.GenQuest.EncGirl.PirateIdx,pchar.GenQuest.EncGirl.PirateName1,NAME_NOM)+"  ganimetin hepsini kendi sakladığı yere götürürdü. Ama artık pes etmeyeceğiz! Sandıklarının nerede olduğunu göster bize!";
			link.l1 = "Doğrusu, kaptanınızın hazinesini korumak için burada değilim, ama yeri sana gösteremem... Çünkü nerede olduğunu bilmiyorum.";
			link.l1.go = "Node_10";
		break;
		
		case "Node_10":
			dialog.text = "Yalan söylüyorsun!!! Bu mağaradan altının kokusunu alabiliyorum! Ölmek istemiyorsan bana yeri göster!";
			link.l1 = "Sözlerimin seni ikna edemediğini görüyorum. Belki kılıcım daha etkili olur?";
			link.l1.go = "Node_11";
		break;
		
		case "Node_11":
			pchar.GenQuest.EncGirl = "RapersTreasure";
			dialog.text = "Sen "+GetSexPhrase("it","pislik")+"Yolumdan çekil!";
			link.l1 = "Argh!";
			link.l1.go = "exit_fight";
		break;
		
		case "EncGirl_Berglar":
			dialog.text = "Merhaba, iyi "+GetSexPhrase("adam","hanımefendi")+". Senin hakkında şikayetler aldık.";
			link.l1 = "Kimden şikayet var? O fahişeden mi?";
			link.l1.go = "EncGirl_Berglar1";
		break;
		
		case "EncGirl_Berglar1":
			dialog.text = "Diline dikkat et, tamam mı? Kız kardeşime hakaret etmene izin vermem! Önce ormanda ona saldırdın, sonra da buraya getirdin "+GetSexPhrase("daha fazla edepsizlik için","ve beni soydu")+".";
			link.l1 = "Hey dostum, bunların hepsini gerçekten dinlemek zorunda mıyım?";
			link.l1.go = "EncGirl_Berglar2";
		break;
		
		case "EncGirl_Berglar2":
			pchar.GenQuest.EncGirl.BerglarSum = makeint(sti(pchar.money)/5) + 5000;
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 250000) pchar.GenQuest.EncGirl.BerglarSum = 220000 + rand(30000);
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 0)
			{
				dialog.text = "Hayır. Sadece mütevazı bir miktar "+sti(pchar.GenQuest.EncGirl.BerglarSum)+" peso seni tüm dertlerinden kurtaracak.";
				if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.BerglarSum))
				{
					link.l1 = "Eh, soylu işler bu devirde biraz pahalıya patlıyor doğrusu. Peki, al bakalım...";
					link.l1.go = "EncGirl_Berglar3";
				}	
				link.l2 = "Bence seni yolumdan çekmek için karnında bir delik açmak daha ucuza gelir.";
				link.l2.go = "EncGirl_Berglar4";
			}
			else
			{
				dialog.text = "Hayır. Ama sen de ceplerini ters çevir, yoksa seni bıçaklarım!";
				link.l1 = "Pekâlâ, al bakalım, seni alçak! Ama bununla paçayı sıyıramayacaksın...";
				link.l1.go = "EncGirl_Berglar3_1";
				link.l2 = "Çıkış yolumda duracağına, karnında bir delik açmak daha kolay olurdu bence.";
				link.l2.go = "EncGirl_Berglar4";				
			}			
		break;
		
		case "EncGirl_Berglar3":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.BerglarSum)));
			dialog.text = "Çok iyi. Kurtulmamız iyi oldu.";
			link.l1 = "İyi şanslar.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoom");			
		break;
		
		case "EncGirl_Berglar3_1":
			dialog.text = "Elbette yapmam, elbette... Peki, sana hoşça kal, "+GetSexPhrase("dostum","kız")+"."+GetSexPhrase(" Ve unutma, öyle yakışıklı değilsin ki herhangi bir kız seni görür görmez sana vurulsun. Sana vereceğim ders bu olsun.","")+"";
			link.l1 = ""+GetSexPhrase("Kesinlikle öyle!..","Defol git artık!")+"";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoomRaped");			
		break;
		
		case "EncGirl_Berglar4":
			dialog.text = "Sen   görünüyorsun "+GetSexPhrase("böylesine asil bir adam","böylesine iyi yetişmiş bir hanımefendi")+", neden bu kadar kaba konuşuyorsun?";
			link.l1 = "Bana en çok bu yakışıyor...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_fight");
		break;
		
		case "Node_2":
			dialog.text = "Peki, sen istedin! Gıdıklayalım mı h"+GetSexPhrase("im","er")+" çelikle, çocuklar? ";
			Link.l1 = "Ölmeden önce dua et!";
			Link.l1.go = "Exit_Fight";
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = "Yani, katılmak istiyor musun yoksa istemiyor musun? "+GetSexPhrase("Defol, burada hepimize yetecek kadar yok","Defol git, bir kız bize yeter")+"!";
			Link.l1 = "O halde, seni rahatsız etmeyeyim.";
			Link.l1.go = "Exit_NoFight";
			Link.l2 = "Burada hiçbir şiddete izin vermem!";
			Link.l2.go = "Node_2";
		break;				
	}
}
