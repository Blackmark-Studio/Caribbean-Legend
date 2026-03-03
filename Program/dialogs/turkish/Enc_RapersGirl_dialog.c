void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iRnd, iRnd1;
	string sTemp, sGems;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit_1":
			AddDialogExitQuest("LandEnc_RapersTalk");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "exit":
			LAi_SetCitizenTypeNoGroup(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Begin_1":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Kaptan","Hanımefendi")+"! Lütfen, merhamet et! Beni koru, yalvarıyorum sana!","Yardım edin! "+GetSexPhrase("Yabancı","Genç hanımefendi")+", kurtar beni, yalvarıyorum!");
			link.l1 = LinkRandPhrase("Ne oldu?","Ne oluyor?",RandPhraseSimple("Ne oldu, bir sorun mu var?","Ne oluyor?"));
			link.l1.go = "Begin_11";
		break;

		case "Begin_2":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Kaptan! Kaptan","Kız! Kız")+", lütfen bekleyin!","Bekle, "+GetSexPhrase("Kaptan","genç hanım")+"! Lütfen.");
			link.l1 = LinkRandPhrase("Ne oldu?","Ne var ne yok?",RandPhraseSimple("Ne oldu, bir sorun mu var?","Ne oluyor?"));
			link.l1.go = "Begin_21";
		break;

		case "Begin_3":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = "Oh, m"+GetSexPhrase("ister","iss")+"! Lütfen, zavallı bir kıza yardım edin, yalvarıyorum! O insanlar bana korkunç bir şey yapmak istiyorlar!";
			link.l1 = LinkRandPhrase("Ne oldu?","Ne var ne yok?",RandPhraseSimple("Ne oldu?","Ne oluyor?"));
			link.l1.go = "Begin_31";
		break;
		
		case "Begin_11":
			dialog.text = RandPhraseSimple("Bu alçaklar bana tecavüz edecek! Ne olur, onları durdurun!","Tanrı aşkına, beni bu canavarlardan koruyun! Onlar beni rezil edecekler!");
			link.l1 = "Panik yapmayı bırak"+GetSexPhrase(", güzelim","")+" . Burada ne oldu?";
			link.l1.go = "exit_1";
		break;

		case "Begin_21":
			dialog.text = RandPhraseSimple("Beni tecavüzcüler kovalıyor!"+GetSexPhrase(" Bir hanımefendinin onurunu savunur musun?","")+"","Kaptan, "+GetSexPhrase("adam ol","sen de bir kadınsın")+" bir kızı rezillikten kurtarmaz mıydın!");
			link.l1 = "Panik yapmayı bırak"+GetSexPhrase(", güzelim","")+". Burada ne oldu?";
			link.l1.go = "exit_1";
		break;
		
		case "Begin_31":
			dialog.text = "Beni kovalıyorlar! Haydutlar! Onlara, beni rahat bıraksınlar, de!";
			link.l1 = "Panik yapmayı bırak"+GetSexPhrase(", güzelim","")+". Burada ne oldu?";
			link.l1.go = "exit_1";
		break;
		
		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = LinkRandPhrase("Yardım edin! Yardım edin! Peşimdeler! Kurtarın beni!","Aaah! Yardım edin, "+GetSexPhrase("yabancı","genç hanım")+"   Beni bu alçaklardan kurtarın!   ","Bana merhamet et ve beni bu alçaklardan koru! Lütfen!");
			Link.l1 = LinkRandPhrase("Ne oluyor?","Ne var ne yok?","Ne oldu?");
			Link.l1.go = "Node_2";			
		break;        

		case "Node_2":
			dialog.text = LinkRandPhrase("Beni... beni tecavüz edecekler! Ne olur, Tanrı aşkına, engel ol! Lütfen!","Bu yaratıklar... Korkunç bir şey planlıyorlar... Beni onlardan koru, lütfen!","Tanrımızın adıyla, beni bu azgın yaratıklardan kurtar! Onlar beni lekelemek istiyorlar!");
			Link.l1 = "Hadi her şeyi çözelim, o zaman.";
			Link.l1.go = "exit_1";			
		break;

		case "ThanksForHelp":
			if(pchar.GenQuest.EncGirl == "Begin_11")
			{
				if(rand(1) == 0)
				{
					dialog.text = RandPhraseSimple("Teşekkür ederim, "+GetSexPhrase("Kaptan","genç hanımefendi")+". Çok korkmuştum!","Beni kurtardığın için teşekkür ederim! Sana minnettarım!");
					link.l1 = "Pekâlâ, "+GetSexPhrase("güzellik","sevgili")+", sakin ol, hepsi geçmişte kaldı.";
					link.l1.go = "Node_11";
				}
				else
				{
					dialog.text = "Ah, çok teşekkür ederim, "+GetSexPhrase("asil bir adam! Gerçekten tam bir centilmeniniz!","Hanımefendi! Beni kurtardınız!")+"";
					link.l1 = "Başka türlü yapamazdım.";
					link.l1.go = "Node_12";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_22")
			{
				if(rand(1) == 0)
				{
					dialog.text = "Ah, teşekkür ederim, "+GetSexPhrase("asil bir adam! Gerçekten tam bir centilmensiniz!","Yabancı! Beni kurtardın!")+"";
					link.l1 = "Başka türlü yapamazdım.";
					link.l1.go = "Node_12";	
				}
				else
				{
					dialog.text = "Ne yaptın sen? Neden onları öldürdün?! Şimdi beni aramaya gelecekler! Tanrım, ben ne yaptım da bunu hak ettim!";
					link.l1 = "İşte minnettarlık dedikleri bu!";
					link.l1.go = "Node_22";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_33")
			{
				dialog.text = "Ne yaptın, "+GetSexPhrase("kaptan","genç hanım")+"?! Neden onları öldürdün? Aslında babam tarafından gönderilmişlerdi... Aman Tanrım, şimdi kesin beni öldürecek...";
				link.l1 = "Bu gerçekten haber! Peki sen ne düşünüyordun, haydutlar tarafından kovalandığını bağırırken?!";
				link.l1.go = "Node_31";
			}
		break;
		
		case "Node_11":
			Diag.TempNode = "Node_1Next";
			addMoneyToCharacter(pchar, makeint((sti(pchar.rank))*25 + frand(2)*500));
			dialog.text = "Biraz param var, lütfen bunu minnettarlığımın bir göstergesi olarak kabul edin. Şimdi herkese anlatacağım, "+GetSexPhrase("ne kadar iyi ve asil bir adamsın","ne kadar iyi ve asil bir kadınsın")+".";
			link.l1 = "Elbette yapacaksın. Teşekkür ederim... Şimdi sadece eve git.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "Node_12":
			dialog.text = "Hâlâ kendime gelemedim. Lütfen bana getirir misin "+GetSexPhrase("bir hanımefendi","ben")+"  yerleşimine "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"? Biliyor musun, şimdi bana her çalının arkasında bir tecavüzcü saklanıyormuş gibi geliyor.";
			link.l1 = RandPhraseSimple("Bu kadar endişelenme, gerçekten... Tamam, hadi gidelim.","Sen tam bir korkaksın, değil mi? Peki, seni oraya götüreceğim.");
			link.l1.go = "Node_121Next";
			link.l2 = "Üzgünüm canım, ama gerçekten hiç vaktim yok, fazlasıyla meşgulüm.";
			link.l2.go = "Node_3End";
		break;
						
		case "Node_22":
			dialog.text = "Sadece onları korkutup kaçırmanı bekliyordum! Şimdi beni yerleşimdeki meyhaneye götürmelisin "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", sana yardım için başvurabileceğim başka kimsem yok.";
			link.l1 = "Ah, kahretsin! Tamam, hadi gidelim. Sadece geride kalma.";
			link.l1.go = "Node_122Next";
			link.l2 = "Hayır, hepsi bu, "+GetSexPhrase("güzellik","sevgili")+"! Bugünlük sürprizlere doydum. Sana yardım edecek başka birini bul.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_31":
			dialog.text = "Ben ne yapacaktım ki?! Babam beni o tefecinin oğluyla evlendirmek istiyor, o süt çocuğuyla... sadece babasının kasasında servet var diye! Ama ben başka birini seviyorum! Lütfen beni ona götür...";
			link.l1 = "Ne büyük bir yük oldun! Peki, tamam, gidelim. Artık seni burada bırakamam, değil mi?.. Seçtiğin kişinin adı ne, seni nereye götüreyim?";
			link.l1.go = "Node_32";
			link.l2 = "Hayır, bu kadar, "+GetSexPhrase("güzellik","sevgili")+"! Bugünlük sürprizlere doyduğum yetti. Sana yardım edecek başka birini bul.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_32":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "Adı "+pchar.GenQuest.EncGirl.sLoverId+", o yeni geldi. Şu anda   yerleşiminde kalıyor "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", orada iş bulmaya çalıştım ama şu sıralar işler zor. Herkes sürekli bir krizden bahsediyor... Ve artık benim için eve dönmek de mümkün değil.";
			link.l1 = "Bir kriz mi? Ha... Gerçek bir korsan için kriz, ufukta bir ticaret kervanı görünüp de yelkenleri dolduracak rüzgar olmadığında olur...";
			link.l1.go = "Node_12Next";
		break;
		
		case "Node_12Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "FindLover";
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_121Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_253";
			pchar.GenQuest.EncGirl = "FindCoins";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_122Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_12End":
			Diag.TempNode = "Node_12End";
			dialog.text = RandPhraseSimple("Biliyor musun, "+GetSexPhrase("kaptan","genç hanım")+"? O kadar korktum ki, bacaklarım hâlâ biraz titriyor.","Ah, biliyor musun, çok korkmuştum. Tanrı'nın seni karşıma çıkarması harika bir şey.");
			link.l1 = RandPhraseSimple("Tanrıya şükür, hâlâ hayattasın.","Bunu bu kadar kafana takma. Böyle olması iyi oldu, biliyor musun.");
			link.l1.go = "exit";
		break;
		
		case "Node_1Next":
			dialog.text = RandPhraseSimple("Teşekkür ederim, "+GetSexPhrase("kapitan","genç hanım")+", bir kez daha. Gerçekten, sana çok minnettarım.","Çok teşekkür ederim, "+GetSexPhrase("kaptan","genç hanım")+". Senin yardımın olmasaydı ne yapardım, hiç bilmiyorum.");
			link.l1 = RandPhraseSimple("Bu sana ders olsun. Peki, bol şans...","Bir dahaki sefere daha dikkatli olmalısın... Şimdi, evine koş, yapacak işlerim var.");
			link.l1.go = "Node_1End";
			link.l2 = "Bu kadar dikkatsiz nasıl olabildin? Neden tek başına ormana girdin?";
			link.l2.go = "Node_13";
		break;
		
		case "Node_1End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_3End":
			Diag.TempNode = "Node_3Final";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "Node_3Final":
			Diag.TempNode = "Node_3Final";
			dialog.text = RandPhraseSimple("Fikrini değiştirdin mi?","Kaptan, fikrinizi değiştirmiş olmanız harika!");
			link.l1 = RandPhraseSimple("Hayır, hayır, canım, ben almayayım.","Boşuna umutlanma...");
			link.l1.go = "exit";
		break;
		
		case "Node_13":
			if(pchar.GenQuest.EncGirl == "FindCoins") 
			{
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
				pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			}
			pchar.GenQuest.EncGirl = "Begin_11";
			switch(sti(pchar.GenQuest.EncGirl.variant))
			{
				case 0:
					if(rand(1) == 0)
					{
						dialog.text = "Muhtemelen bana güleceksin ama... Bir aşk iksiri için malzeme topluyordum... Bir cadı, kalp meselelerine iyi gelebilecek bir kök olduğunu söyledi.";
						link.l1 = "Aman Tanrım! Ne "+GetSexPhrase("bu kadınlar ne düşünüyor","aklından geçen neydi")+"?! Görünen o ki, epey talibin olmuş, peşinden koşanlar çoktu ve hepsini savuşturmak bana zor geldi. Ha-ha-ha-ha... Hoşça kal.";
						link.l1.go = "Node_1End";
					}
					else
					{
						dialog.text = "Sadece biraz ot toplamak ve temiz hava almak için dışarı çıkmıştım. Görünüşe göre yürüyüş için en iyi zaman değilmiş.";
						link.l1 = "Ne dikkatsizlik! Neyse ki zamanında yetiştim. Sana bol şans dilerim.";
						link.l1.go = "Node_1End";
					}
				break;
				case 1:
					dialog.text = "Hanımım burada bir yerde yürüyüş yaparken kolyesindeki incileri düşürmüş. Eve döndüğünde bana bağırdı ve hepsini bulup getirmemi emretti. 'Hepsini bulmadan sakın buraya dönme!' dedi. Ama tam olarak nerede düştüklerini bile bilmiyorum ki. Ayrıca, bu sık otların arasında onları nasıl bulacağım? İnciler o kadar küçük ki... Yani, burada öylece dolaşıyorum, ne yapmam gerektiği hakkında en ufak bir fikrim yok...";
					link.l1 = "Peki, nasıl bir kolyeydi? Belki de ormanda dolaşmak yerine yenisini almak daha kolay olurdu? Hanımınız kaç inci kaybetmiş?";
					link.l1.go = "Node_131";
				break;
				case 2:
					dialog.text = "Rahmetli babam bana bir harita bıraktı, ve onun eski dostları bunu benden almak istediler. O hayattayken hepsi ondan korkardı, ama onu toprağa verdikten sonra sıkıntılı günler başladı. Önce bu haritayı satın almak istediler, ama kabul etmedim, sonra da beni korkutmaya başladılar.";
					link.l1 = "Peki neden onu satmadın? Bu harita hakkında korsan çetelerinin peşine düşeceği kadar özel olan ne var?";
					link.l1.go = "Node_132";
				break;
			}	
		break;
		
		case "Node_131":
			pchar.GenQuest.EncGirl.SmallCoins = rand(25) + 20;
			pchar.GenQuest.EncGirl.BigCoins = rand(15) + 5;
			dialog.text = "O kolye seçilmiş incilerden yapılmıştı, onlar ucuza alınamaz. Orada "+sti(pchar.GenQuest.EncGirl.BigCoins)+" büyük inciler ve "+sti(pchar.GenQuest.EncGirl.SmallCoins)+" daha küçükleri. Eğer o inciler bulunsaydı, onun gibi bir kolye daha yaptırabilirdik.";
			link.l1 = "Bu işin kolay olmayacağı kesin... Neyse, hanımın sana emir verdiyse, yapacak pek bir şey yok. İncileri bulmaya çalış. İyi şanslar.";
			link.l1.go = "Node_131End";
			link.l2 = "Bu anlamsız. Bu kalın otların arasında inci bulmak, samanlıkta iğne aramaktan daha zor. Üstelik incilerin kaybolduğu yeri bile bilmiyorsun...";
			link.l2.go = "Node_133";
		break;
		
		case "Node_131End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
			pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132":
			pchar.GenQuest.EncGirl.mapOwner = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1); 
			dialog.text = "Babam, hazinesini sakladığı yeri haritada işaretlemişti. Ünlü korsan hakkında bir şey duydun mu "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.mapOwner,NAME_VOC)+"?";
			link.l1 = "Hayır, hiç duymadım.";
			link.l1.go = "Node_132_1";
		break;
		
		case "Node_132_1":
			dialog.text = "Pekala, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.mapOwner,NAME_NOM)+" babamdı. Herkes ondan korkardı, kimse tek kelime etmeye cesaret edemezdi. Şimdi ise yüzsüzleştiler tabii. Haritayı satmayı reddedince, onlar da hazineden paylarını almaları gerektiğini söylediler. Haritayı saklamak istedim ama yine de izimi buldular...";
			link.l1 = "Ve neden en başta bunu sakladın ki? Bir gemi kirala, git ve hazineni al. Baban bunu boşuna saklamamıştır.";
			link.l1.go = "Node_132_2";
		break;
		
		case "Node_132_2":
			dialog.text = "Bunu söylemek kolay da yapmak zor. Bir gemi kiralayacak param yok, hem... Korkarım... Hazineyi nasıl kazacağım, gemiye nasıl taşıyacağım... Sonra da nereye götüreceğim? Yol boyunca herkes bana kolayca saldırabilir...";
			link.l1 = "İyi bir noktaya değindin... Peki, haritanı sakla o zaman. Ama onu iyi bir yere koymayı unutma.";
			link.l1.go = "Node_132_2End";
			if(GetCharacterItem(pchar, "map_full") == 0)
			{
				link.l2 = "Hmm... Muhtemelen doğru. O yüzden satmalıydın zaten.";
				link.l2.go = "Node_132_3";
			}
			link.l3 = "Bir yol arkadaşı bulmayı denedin mi?";
			link.l3.go = "Node_132_8";	
		break;
		
		case "Node_132_2End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_3":
			dialog.text = "Böyle bir fırsatı kaybetmek beni üzüyor... Babam oraya sakladığı hazinelerden bahsetmişti. Kimse bana o kadar para vermezdi...";
			link.l1 = "Pekâlâ, onu ucuza satma. Hem, altın hayatından daha değerli değil. Üstelik, bu senin için en kolay yol: paranı alıp bütün dertlerinden kurtuluyorsun...";
			link.l1.go = "Node_132_4";
		break;
		
		case "Node_132_4":
			pchar.GenQuest.EncGirl.mapPrice = 20000 + 500 * sti(pchar.rank);
			dialog.text = "Bu kulağa cazip geliyor... Peki bunun için bana ne kadar teklif edebilirsin?";
			link.l1 = "Bence bundan daha değerli olamaz "+sti(pchar.GenQuest.EncGirl.mapPrice)+" pesos.";
			link.l1.go = "Node_132_5";
		break;
		
		case "Node_132_5":
			if((GetSummonSkillFromName(pchar, SKILL_COMMERCE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)) > (rand(220) + 100) && (makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
			{
				dialog.text = "Heh, kadın olmak kolay değil... Peki, kabul ediyorum. Sonunda bu kâbus bitecek... Belki de bu haritanın sana ait olması en iyisi,"+GetSexPhrase(" asil bir beyefendi","")+", o alçaklara göre daha iyi.";
				link.l1 = "Güzel. Al paranı... sadece hepsini bir anda harcamamaya çalış.";
				link.l1.go = "Node_132_6";
			}
			else
			{
				dialog.text = "Hayır, "+GetSexPhrase("kapitan","genç hanım")+". Bunu satmayacağım. İyi bir adamla evleneceğim ve sonra hazineyi birlikte bulacağız.";
				link.l1 = "Bu sana kalmış. Zaten o kağıt parçasının artık bir değeri yok.";
				link.l1.go = "Node_132_2End";
			}	
		break;
		
		case "Node_132_6":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.mapPrice))); 
			ref rMap = ItemsFromID("map_full"); // mitrokosta фикс пустой карты
			FillMapForTreasure(rMap, "");
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_8":
			dialog.text = "Onları nerede bulacağım peki? Gençler güvenilir değil, hazinelerden çok başka şeylerle ilgileniyorlar. Yaşlılardan ise çekiniyorum, hepsi bana babamın arkadaşlarını hatırlatıyor. O kadar kurnaz ve hainler ki, onlardan ne bekleyeceğini asla bilemezsin.";
			link.l1 = "Ha-ha-ha... Peki, ama beni de yanında götürecek misin?";
			link.l1.go = "Node_132_9";
		break;
		
		case "Node_132_9":
			dialog.text = "Sen mi? Ve sen gidecek misin? Ama o zaman beni buraya, yerleşkeye geri getirmek zorunda kalacaksın "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", tamam mı?";
			link.l1 = "Pekâlâ, sana söz veriyorum. Sadece bana yolu göster.";
			link.l1.go = "Node_132_10";
		break;
		
		case "Node_132_10":
			EncGirl_GenQuest_GetChestPlaceName();
			dialog.text = "Hazine mağarada saklı "+XI_ConvertString(pchar.GenQuest.EncGirl.islandId+"Acc")+",  karaya çıkmamız gerekiyor "+XI_ConvertString(pchar.GenQuest.EncGirl.shoreId+"Gen")+", kendimi göstereceğim yer... Ama unutma, sadece yarısını alacaksın!";
			link.l1 = "Pekâlâ, sana ihanet etmeyeceğim, söz veriyorum. Beni takip et ve geride kalma.";
			link.l1.go = "Node_132_11";
		break;
		
		case "Node_132_11":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "4");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
			AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_Death.function = "EncGirl_Death";
			pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
			pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
			SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
			SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "GetChest";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_11_1":
			dialog.text = "Kaptan, şimdi mağarayı bulmalıyız.";
			link.l1 = "Pekala, şimdi bir bakalım.";
			link.l1.go = "exit";
			Diag.TempNode = "Node_132_11_2";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;
		
		case "Node_132_11_2":
			Diag.TempNode = "Node_132_11_2";
			dialog.text = "Kaptan, mağarayı bulmalıyız.";
			link.l1 = "Pekala, şimdi bir bakalım.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_12":
			dialog.text = "İşte! Buldum! Babamın dediği gibi! Kocaman bir hazine yığını! Anlaştığımız gibi, yarısı senin.";
			link.l1 = "Gördün mü? Zor olmadı, korkacak bir şey yokmuş.";
			link.l1.go = "Node_132_13";
		break;
		
		case "Node_132_13":
			dialog.text = "Ha-ha-ha! Artık zenginim! Payını şimdi alacak mısın?";
			link.l1 = "Sanırım.";
			link.l1.go = "Node_132_15";
		break;
		
		case "Node_132_15":
			dialog.text = "O zaman al, ve lütfen şu eşyaların hepsini gemiye taşımama yardım et. Hâlâ beni eve götüreceğine dair verdiğin sözü hatırlıyor musun?";
			link.l1 = "Unutmadım! Tabii ki seni götüreceğim.";
			link.l1.go = "Node_132_16";
		break;
		
		case "Node_132_16":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.		
			LAi_LocationDisableMonstersGen(pchar.location, false);
			chrDisableReloadToLocation = false;
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 2+hrand(6));
			TakeNItems(pchar, "jewelry1", 30+hrand(15));
			TakeNItems(pchar, "jewelry2", 30+hrand(15));
			TakeNItems(pchar, "jewelry3", 30+hrand(15));
			TakeNItems(pchar, "jewelry4", 30+hrand(15));
			TakeNItems(pchar, "jewelry5", 30+rand(10));
			TakeNItems(pchar, "jewelry6", 10+rand(10));
			TakeNItems(pchar, "jewelry42", 20+rand(10));
			TakeNItems(pchar, "jewelry44", 30+rand(10));
			TakeNItems(pchar, "jewelry46", 50+rand(20));
			AddQuestRecord("JungleGirl", "6");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));		
			pchar.GenQuest.EncGirl = "ChestGetted";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
			Diag.TempNode = "Node_132_17";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			pchar.quest.EncGirl_AddPassenger.win_condition.l1 = "location";// лесник на корабль девицу. 
			pchar.quest.EncGirl_AddPassenger.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.EncGirl_AddPassenger.function = "EncGirl_AddPassenger";
		break;
		
		case "Node_132_17":
			Diag.TempNode = "Node_132_17";
			dialog.text = "Zengin olmak gerçekten harika! Şimdi kendimi bambaşka hissediyorum."; 
			link.l1 = "Senin adına sevindim.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_18":
			dialog.text = "Pekala, kaptan. Yolculuğum burada sona eriyor. Yardımlarınız için teşekkür ederim.";
			link.l1 = "Rica ederim... Peki, bu yeni servetinle ne yapmayı düşünüyorsun? Kölelerle birlikte bir plantasyon mu alacaksın?";
			link.l1.go = "Node_132_19";
		break;
		
		case "Node_132_19":
			dialog.text = " Bilmiyorum, henüz karar vermedim. Belki Avrupa'ya taşınırım... ";
			link.l1 = "Pekala, o zaman! Sana bol şans.";
			link.l1.go = "Node_132_20";
		break;
		
		case "Node_132_20":
			dialog.text = "Dur bir dakika... Bu süs eşyası babamın hazineleri arasındaydı. Benim için bir anlamı yok, ama belki sen beğenirsin. Lütfen, bana yaptıkların için kişisel bir teşekkürüm olarak bunu kabul et. Bu benim payımdan, ha-ha-ha!";
			link.l1 = "Vay canına, bu gerçekten harika bir hediye. Teşekkür ederim"+GetSexPhrase(", güzelim","")+" . Kendine iyi bir damat bul, olur mu... ";
			link.l1.go = "Node_132_21";
		break;
		
		case "Node_132_21":
			chrDisableReloadToLocation = false;		
			RemovePassenger(pchar, npchar);			
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "8");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
            LAi_SetActorType(npchar); // отправил восвояси чтоб не стояла. лесник.
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
            pchar.quest.EncGirl_EnterToSea.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.	
            PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.						
		break;
		
		case "Node_133":
			dialog.text = "Ama ne yapabilirim? Hanımımın emirlerini görmezden gelemem, beni canlı canlı yüzebilir.";
			link.l1 = "Beni   yerleşimdeki   kilisede   bekle "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", sana yeni bir kolye yapmak için incileri getireceğim.";
			link.l1.go = "Node_133_1";
			if(sti(pchar.money) >= 15000)
			{
				link.l2 = "Al bakalım. Şu 15.000 peso senin olsun. Bu, kolyeye uygun incileri seçmek ya da yenisini almak için fazlasıyla yeterli olacaktır.";
				link.l2.go = "Node_135";
			}							
		break;
		
		case "Node_133_1":
			pchar.GenQuest.EncGirl = "GetCoins";
			pchar.quest.EncGirl_Coins.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_Coins.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_Coins.function = "EncGirl_toChurch";
			pchar.quest.EncGirl_GetCoins.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.function = "EncGirl_GenQuest_GetCoins";	
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");// лесник - девица убегает если ГГ сказал ждать в цервки
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);			
			Diag.TempNode = "Node_134"; 
			Diag.CurrentNode = Diag.TempNode;
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "1"); 
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","")); 
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sText1", sti(pchar.GenQuest.EncGirl.BigCoins)); 
			AddQuestUserData("JungleGirl", "sText2", sti(pchar.GenQuest.EncGirl.SmallCoins)); 		
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_134":
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Kaptan","Genç hanımefendi")+",   seni tekrar gördüğüme çok sevindim! Kolye için incileri toplamayı başardın mı?","Merhaba, kaptan! İncileri getirdin mi? Biliyor musun, hanımım oldukça endişelenmeye başladı...");
			if (GetCharacterItem(pchar, "jewelry52") >= sti(pchar.GenQuest.EncGirl.BigCoins) && GetCharacterItem(pchar, "jewelry53") >= sti(pchar.GenQuest.EncGirl.SmallCoins))
			{
				link.l1 = "Evet. İşte incilerin. Onları hanımına götür ve bir dahaki sefere daha dikkatli olmasını söyle.";
				link.l1.go = "Node_134_1";
			}
			else
			{
				link.l1 = "Daha değil. O kadar kolay değil, biliyorsun... Ama getireceğim, bekle ve gör.";
				link.l1.go = "Node_134_2";
			}	
		break;
		
		case "Node_134_1":
			TakeNItems(pchar, "jewelry52", -sti(pchar.GenQuest.EncGirl.BigCoins)); 
			TakeNItems(pchar, "jewelry53", -sti(pchar.GenQuest.EncGirl.SmallCoins)); 
			pchar.quest.EncGirl_GetCoins.over = "yes";
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			dialog.text = "Oh, "+GetSexPhrase("Kaptan","genç hanım")+",   seninle tanıştığıma o kadar mutluyum ki! Bana yaptığın her şey için minnettarlığımın bir göstergesi olarak, sana bu küçük takıyı ve şu değerli taşları vermek istiyorum. Umarım işine yararlar.";
			link.l1 = "Vay canına! Sana da teşekkürler"+GetSexPhrase(", güzelim","")+", beklemiyordum... Elveda, mutlu ol.";
			link.l1.go = "Node_134_End";
		break;
		
		case "Node_134_2":
			dialog.text = "Ah, "+GetSexPhrase("kapitan","genç hanım")+", sana güveniyorum.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_SetStayType(NPChar);
		break;
		
		case "Node_134_End":
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			TakeNItems(pchar, "jewelry1", 15+hrand(8));
			AddQuestRecord("JungleGirl", "2");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_135":
			addMoneyToCharacter(pchar, -15000);
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			dialog.text = "Ah, "+GetSexPhrase("kaptan","genç hanımefendi")+", bugün bana ikinci kez yardım ettin. Sana minnettarım. İyiliğini asla unutmayacağım.";
			link.l1 = "Rica ederim. Hanımına selam söyle...";
			link.l1.go = "Node_135End";
		break;
		
		case "Node_135End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			NPChar.lifeDay = 0;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;	
		
		case "ThanksForSave":
			if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga") 
			{
				if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse")) 
				{
					iRnd = 2;
					pchar.GenQuest.EncGirl.BrothelCity = true;
				}	
				else
				{	
					iRnd = 1;
				}	
			}
			else
			{
				iRnd = 1;
			}
			switch(rand(iRnd))
			{
				case 0:
					dialog.text = RandPhraseSimple("Onlara hiç para vermemeliydin. Yalan söylüyorlardı.","Onlara inanma. Onlar yalancı. Ve onlara hiç para vermemeliydin.");
					link.l1 = "Onları öldürmeli miydim?";
					link.l1.go = "Node_200";
				break;
				case 1:
					dialog.text = "Oh, ne asil bir davranış! Senin hemen böyle biri olduğunu anlamıştım "+GetSexPhrase("gerçek bir centilmen","soylu bir hanımefendi")+"! Lütfen, en içten teşekkürlerimi kabul edin. Umarım o serserilerin söylediklerine inanmadınız?";
					link.l1 = "Önemli değil. Bir kız ve bir avuç serseri ormanda, bu öylesine doğal ki...";
					link.l1.go = "Node_210";
					link.l2 = "Ne diyorsun, "+GetSexPhrase("güzellik","sevgili")+"? Nasıl yapabilirim ki?";
					link.l2.go = "Node_211";
				break;
				case 2:
					dialog.text = "Teşekkür ederim, kaptan. Sizi bu tatsız işe bulaştırdığım için üzgünüm, ama gerçekten başka çarem yoktu.";
					link.l1 = "Pekâlâ, senin de epeyce sıkışıp kaldığını görüyorum. Nasıl oldu da bu hâle geldik?";
					link.l1.go = "Node_220";		
				break;
			}
		break;
		
		case "Node_200":
			if(rand(1) == 0)
			{
				dialog.text = "Belki de... Artık beni asla rahat bırakmayacaklar.";
				link.l1 = "Ah, hadi ama! Artık korkacak bir şeyin yok, eve git.";
				link.l1.go = "Node_200End";
				link.l2 = "Vay canına! Neden erkeklere bu kadar mesafelisin?";
				link.l2.go = "Node_201";
			}
			else
			{
				dialog.text = "Elbette hayır! Ama yine de peşimi bırakmayacaklar. Beni şu yerleşkeye götürür müsün "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", lütfen?";
				link.l1 = "Eve git, sana dokunmazlar. Şimdi kolay kazandıkları parayı harcamak için meyhaneye gidiyor olmalılar.";
				link.l1.go = "Node_200End";
				link.l2 = RandPhraseSimple("Bu kadar endişelenme, gerçekten... Tamam, hadi gidelim.","Ne kadar korkaksın, değil mi? Peki, seni oraya götüreceğim..");
				link.l2.go = "Node_121Next";
			}
		break;
		
		case "Node_201":
			dialog.text = "Ah hayır, ne diyorsun? Bu alçakları çok iyi tanıyorum. Onlar babamın eski dostları. Babamın hazinelerini sakladığı yeri bulmaya çalışıyorlar.";
			link.l1 = "Peki ya babanla ne işin var?";
			link.l1.go = "Node_202";
		break;
		
		case "Node_202":
			dialog.text = "Eskiden bir korsan gemisinin kaptanıydı. Yakın zamanda öldü... Cenazede hepsi çok saygılıydı, ama zaman geçtikçe onu unuttular, ardından da onurlarını ve dürüstlüklerini kaybettiler. İyi ki onları fark ettim. Hazineyi nerede bulacaklarını öğrenir öğrenmez, benim işim biter.";
			link.l1 = "Bu üzücü bir hikaye. Peki, onlardan saklanmaya devam mı edeceksin?";
			link.l1.go = "Node_203";
		break;
		
		case "Node_203":
			dialog.text = "Evde mücevher saklayamam, beni koruyacak kimsem yok. Bu yüzden geceleri mağaraya gidiyorum, param bitince...\nLütfen beni mağaraya götür, sana verdiğim parayı geri vereceğim... Sanırım sen yanımdayken korsanlar peşimize düşmeye cesaret edemezler.";
			link.l1 = "Üzgünüm canım, ama başka planlarım var. Hazineni başka bir zaman toplarsın.";
			link.l1.go = "Node_200End";
			link.l2 = "Pekala, hadi gidelim, eğer benden korkmuyorsan.";
			link.l2.go = "Node_204";
		break;
		
		case "Node_204":
			dialog.text = "Biliyor musun, nedense ben...";
			link.l1 = "Pekâlâ, bu iyi bir şey.";
			link.l1.go = "Node_205";
		break;
		
		case "Node_205":
			Diag.TempNode = "Node_206";
			EncGirl_GenerateChest(npchar);
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_206":
			Diag.TempNode = "Node_206";
			dialog.text = "Kaptan, beni mağaraya götüreceğine söz vermiştin.";
			link.l1 = "Hadi gidelim...";
			link.l1.go = "exit";
		break;
		
		case "Node_207":
			dialog.text = "Pekala, kaptan, ihtiyacım olan her şeyi aldım. Artık dönebiliriz.";
			link.l1 = "Arkadaşların etrafta yok, görüyorum.";
			link.l1.go = "Node_208";
		break;
		
		case "Node_208":
			dialog.text = "Tanrıya şükür. Daha fazla belaya ihtiyacım yok... Al, şu külçeleri al... masraflarını karşılamaya yeter. Yalnız git, ben başka bir yoldan gideceğim...";
			link.l1 = "Pekâlâ, korkmuyorsan sana bol şans.";
			link.l1.go = "Node_209";
		break;
		
		case "Node_209":
			LAi_LocationDisableMonstersGen(pchar.location, false);
			i = makeint(sti(pchar.GenQuest.EncGirl.price)/100.0);
			TakeNItems(pchar, "jewelry6", i);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
			DialogExit();
		break;
		
		case "Node_200End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_210":
			dialog.text = "Hmm, "+GetSexPhrase("kaptan","genç hanım")+", alaycı tavrını hiç beğenmiyorum.";
			link.l1 = "Hazırsın, "+GetSexPhrase("güzellik","sevgili")+". Ve kasabaya gitmek için acele etsen iyi olur, yoksa seni tekrar kovalamaya başlarlar.";
			link.l1.go = "Node_1End";
		break;
		
		case "Node_211":
			dialog.text = "O kadar telaşlandım ki! Beni lütfen yerleşimdeki meyhaneye götürebilir misiniz? "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"? Yoksa, korkarım ki beni tekrar kovalayacaklar.";
			link.l1 = "Belki de haklısın. Hadi gidelim...";
			link.l1.go = "Node_122Next";
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
		break;
		
		case "Node_220":
			dialog.text = "Ah kaptan, bu uzun bir hikaye ve emin değilim ilgini çeker mi. Ama... şimdi senin yardımın olmadan başaramam. Beni yerleşimdeki meyhaneye götürebilir misin lütfen? "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"? Korkarım ki beni bir türlü rahat bırakmadılar.";
			link.l1 = "Üzgünüm canım, buna vaktim yok. Yapmam gereken işler var.";
			link.l1.go = "Node_221";
			link.l2 = "Neden bu kadar gizemlisin?";
			link.l2.go = "Node_222";
		break;
		
		case "Node_221":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_222":
			dialog.text = "Ve herkes benim talihsizliğimden çıkar sağlamaya çalışırken, nasıl açık olabilirim ki?";
			link.l1 = "Pekâlâ, o zaman...";
			link.l1.go = "Node_223";
		break;
		
		case "Node_223":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();		
		break;
		
		case "Node_224":
			dialog.text = "Kaptan, beni yerleşim yerindeki meyhaneye götüreceğine söz vermiştin "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+".";
			link.l1 = RandPhraseSimple("Hatırlıyorum.","Merak etme, orada olacağım.");
			link.l1.go = "exit";
		break;
		
		case "Node_225":
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15)
				{
					dialog.text = "Orada çok fazla insan var. Özel odaya geçelim. Sana bir şey söylemem lazım.";
					link.l1 = LinkRandPhrase("Senin için zaten fazlasıyla şey yaptım, artık hoşça kal.","Lütfumu suistimal etmemelisin. Görüşürüz, canım.","Bundan sonra hikayelerine ihtiyacım yok, her şeyi kendin halledebilirsin.");
					link.l1.go = "Node_226";
					link.l2 = "Hmm, peki. O zaman anahtarları barmenden alacağım.";
					link.l2.go = "Node_227";
				}
				else
				{
					dialog.text = "Yardımınız için çok teşekkür ederim, kaptan. Bunu unutmayacağım.";
					link.l1 = "Ah, zahmet etme. Sadece bundan sonra daha dikkatli olmaya çalış.";
					link.l1.go = "Node_226_1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") // Addon-2016 Jason, французские миниквесты (ФМК)
				{
					dialog.text = "Yardımınız için çok teşekkür ederim, kaptan. Bunu unutmayacağım.";
					link.l1 = "Ah, zahmet etme. Sadece bundan sonra daha dikkatli olmaya çalış.";
					link.l1.go = "Node_226_1";
				}
				else
				{
					dialog.text = "Orada çok fazla insan var. Özel odaya geçelim. Sana bir şey söylemem lazım.";
					link.l1 = LinkRandPhrase("Senin için zaten fazlasıyla şey yaptım, artık hoşça kal.","İyiliğimi suistimal etmemelisin. Görüşürüz, canım.","Artık hikayelerine ihtiyacım yok, bundan sonrasını kendin halledebilirsin.");
					link.l1.go = "Node_226";
					link.l2 = "Hmm, peki. O zaman anahtarları barmenden alırım.";
					link.l2.go = "Node_227";
				}
			}
		break;
		
		case "Node_226":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_226_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_227":
			pchar.GenQuest.EncGirl = "EncGirl_ToTavern";
			pchar.quest.EncGirl_inRoom.win_condition.l1 = "location";
			pchar.quest.EncGirl_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_inRoom.function = "EncGirl_SpeakInRoom";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_228":
			if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse") && CheckAttribute(pchar,"GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15) // душещипательная история о невинной девочке попавшей в бордель
			{
				DeleteAttribute(pchar, "GenQuest.EncGirl.BrothelCity");
				dialog.text = "Hâlâ hikayemi dinlemek istiyor musun?";
				link.l1 = "Hmm... Sanırım gitme vakti geldi. Hoşça kal!";
				link.l1.go = "Node_232";
				link.l2 = "Pekâlâ, söyle bakalım, o zaman.";
				link.l2.go = "Node_233";	
			}
			else						
			{
				dialog.text = "Ah, asil kurtarıcım, sonunda sana bir kadının teşekkür edebileceği tek şekilde teşekkür edebilirim\nSeni ormanda gördüğümde, içimde her şey değişti. Tecavüzcüleri ve yanaklarımı kamçılayan keskin palmiye yapraklarını unuttum. Nereye kaçacağımı, neden kaçacağımı unuttum ... Sadece seni gördüm. Ve sadece seni istedim ... Ve benim için yaptıklarından sonra...";
				link.l1 = "Vay canına! Ne öfke ama! Peşindekiler kimi kovalayacaklarını iyi biliyormuş...";
				link.l1.go = "Node_229"; // ГГ допрыгался - щас его попросту трахнут
				link.l2 = "Dinle güzelim, bunu gayet iyi anlıyorum ama lütfen, öfkeni kendine sakla.";
				link.l2.go = "Node_230"; // Послал в пешее эротическое путешествие
			}
		break;
		
		case "Node_229":
			dialog.text = "Şimdi gel bana, kahramanım...";
			link.l1 = "Ah, sevgilim...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "EncGirl_facking";
			DoQuestCheckDelay("PlaySex_1", 3.0);
		break;
		
		case "Node_230":
			dialog.text = "Ah! Nasıl... Nasıl cüret edersin?! Ne alçak herifsin! Bir kız sana tüm kalbiyle ve ruhuyla teşekkür etti, sen ise...";
			link.l1 = "Eğer bu kadar çok cilve yapıp karşılaştığın ilk adama göz koymasaydın, başın da bu kadar derde girmezdi. Artık ormanda böyle cilveli hanımları kurtarmıyorum...";
			link.l1.go = "Node_231";
		break;
		
		case "Node_231":
			dialog.text = "Böyle sözleri daha önce hiç kimseden duymamıştım! Ve bunu asla affetmeyeceğim! Beni daha çok hatırlayacaksın!";
			link.l1 = "Hadi artık, tamam mı? Biraz toparlan kendini, yoksa yine kurtarılmak mı istiyorsun...";
			link.l1.go = "Node_231_1";
		break;
		
		case "Node_231_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","", -1.0);
			npchar.lifeDay = 0;
			DoQuestFunctionDelay("EncGirl_SetBerglar", 5.0);
			DialogExit();		
		break;
		
		case "Node_232":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_233":
			pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			dialog.text = "Ailem   yerleşim   yerinde   yaşıyor "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.Parents_City)+"Tesadüfen buraya geldim, nişanlımın beni ailesiyle tanıştırmak için götürdüğü gemideydim ama gemiye korsanlar saldırdı. Gemi ele geçirildi ve yolcular buradan çok uzakta olmayan bir koyda karaya bırakıldı. Nişanlım baskın sırasında öldürüldü, ben ise ormanı geçerken ağır hastalandım.\nYerel genelevin patroniçesi beni iyileştirdi, ama ayağa kalkar kalkmaz tedavime harcadığı parayı çalışarak ödememi istedi. Fahişe oldum, ama patroniçenin hoşuna gitmedim, bu yüzden en azından parasının bir kısmını geri almak için beni bazı haydutlara sattı. Geri kalanını zaten biliyorsun.";
			link.l1 = "O zaman bırak işi, eve git! Neden sana köleymişsin gibi davranmalarına izin veriyorsun?!";
			link.l1.go = "Node_234";
		break;
		
		case "Node_234":
			dialog.text = "Yapamam! Bütün eşyalarım: düzgün kıyafetlerim, param, belgelerim... Hepsi genelevde, seyahat çantamda. Onu buluşma odasında sakladım. Ve ben bu haldeyken, limandaki her denizci peşimden koşar. Belgelerim ya da param olmadan kim beni gemisine alır ki? Şimdi ise şehirde yüzümü bile gösteremem, yoksa hapsi boylarım...";
			link.l1 = "Sorun olmaz. Hadi gidelim. Seni bizzat ben eve götüreceğim.";
			link.l1.go = "Node_235";
			link.l2 = "Burada bekle. Seyahat çantanı getireceğim.";
			link.l2.go = "Node_236";													
			if(sti(pchar.money) >= 5000) 
			{
				link.l3 = "Senin belgelerini kim takar? Eve gitmek için ne kadar paraya ihtiyacın var?";
				link.l3.go = "Node_237";							
			}			
		break;
		
		case "Node_235":
			dialog.text = "Ah, teşekkür ederim kaptan... Ama... biliyorsunuz, size ödeyecek hiçbir şeyim yok.";
			link.l1 = "Hangi ödemeden bahsediyorsun? Hadi, bulunmadan gidelim...";
			link.l1.go = "Node_240";				
		break;
		
		case "Node_240":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "20");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			OfficersReaction("bad");
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
			pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
			DialogExit(); 		
		break;
		
		case "Node_236":
			dialog.text = "Ah, kaptan, bilirsiniz ki, asla böyle bir şey sormaya cesaret edemem...";
			link.l1 = "Korkma. Yakında geri döneceğim.";
			link.l1.go = "Node_239";				
		break;		
		
		case "Node_239":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "21");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);

			pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
			if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > rand(100))
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoomUp";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
			}
			else
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoom";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
			}
			pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

			pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";
						
			pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
		
		case "Node_240_1":
			pchar.quest.EncGirl_GetBagFail.over = "yes";
			dialog.text = "Ah, sana bir şey olmuş olmasından zaten endişelenmiştim.";
			if(CheckCharacterItem(pchar, "leather_bag"))
			{
				link.l1 = "Ne olabilir ki? Al, eşyalarını al.";
				link.l1.go = "Node_241";
			}	
			else
			{
				link.l1 = "Dinle, orada hiçbir şey bulamadım. Seyahat çantanı buluşma odasında bıraktığına emin misin?";
				link.l1.go = "Node_242";			
			}	
		break;
		
		case "Node_241":
			TakeNItems(pchar, "leather_bag", -1);
			dialog.text = "Teşekkür ederim, "+GetSexPhrase("asil kaptan","asil kız")+". Bana yaptıklarını asla unutmayacağım. Fazla bir şeyim yok, ama lütfen bu muskayı kabul et. Belki de korsan saldırısı sırasında hayatımı kurtaran bu tılsımdı.";
			link.l1 = "Teşekkür ederim, yolun açık olsun! Hoşça kal şimdi...";
			link.l1.go = "Node_243";
		break;
		
		case "Node_242":
			dialog.text = "Gerçekten çantamı buldular mı?";
			if(sti(pchar.money) >= 5000)
			{
				link.l1 = "Eve dönmek için ne kadar paraya ihtiyacın var?";
				link.l1.go = "Node_237";
			}
			link.l2 = "Belki de öyle oldu. Her neyse, yollarımız burada ayrılıyor. Elveda!";
			link.l2.go = "Node_244";
		break;
		
		case "Node_243":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_244":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_245":
			dialog.text = "Teşekkür ederim, kaptan. Biliyor musunuz, sonunda eve döndüğüme hâlâ inanamıyorum. Lütfen, benimle gelin, sizi ailemle tanıştırayım.";
			link.l1 = "Dinle, "+GetSexPhrase("güzellik","tatlım")+", gerçekten buna hiç vaktim yok. Belki başka bir zaman?";
			link.l1.go = "Node_246";
		break;
		
		case "Node_246":
			dialog.text = "Ne yazık... Peki, o zaman hoşça kal, Tanrı seni korusun. Sana borcumu ödeyemem ama lütfen bu muskayı kabul et.";
			link.l1 = "Teşekkür ederim! Şimdi hemen eve koş, aileni mutlu et!";
			link.l1.go = "Node_247";
		break;
		
		case "Node_247":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);		
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "24");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl","sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			CloseQuestHeader("JungleGirl");
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "Node_248":
		break;
		
		case "Node_237":
			dialog.text = "Pek bilmiyorum... Belki de geçen bir arabayı beklemem gerekecek. Ama senden para isteyemem.";
			if(makeint(pchar.money)>=5000)
			{
				link.l1 = "Anladım. Peki, al 5000 peso. Bu yeterli olmalı.";
				link.l1.go = "Node_237_1";
			}
			if(makeint(pchar.money)>=25000)
			{
				link.l2 = "Anladım. Peki, al 25.000 peso ve evine git.";
				link.l2.go = "Node_237_2";
			}
			if(makeint(pchar.money)>=35000)
			{
				link.l3 = "Anladım. Peki, al 35.000 peso. Bu, gemideki en iyi kamarayı almak için yeterli olmalı.";
				link.l3.go = "Node_237_3";
			}
		break;
		
		case "Node_237_1":
			AddMoneyToCharacter(pchar, -5000);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			dialog.text = "Teşekkür ederim, "+GetSexPhrase("soylu kaptan","asil kız")+". Bana yaptıklarını asla unutmayacağım.";
			link.l1 = "İyi yolculuklar o zaman. Elveda...";
			link.l1.go = "Node_238";
			pchar.GenQuest.EncGirl = "EncGirlFack_GetMoney";
		break;
		
		case "Node_237_2":
			AddMoneyToCharacter(pchar, -25000);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			dialog.text = "Teşekkür ederim, "+GetSexPhrase("asil kaptan","asil kız")+". Bana yaptıklarını asla unutmayacağım.";
			link.l1 = "Öyleyse iyi yolculuklar. Elveda...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_237_3":
			AddMoneyToCharacter(pchar, -35000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			dialog.text = "Teşekkür ederim, "+GetSexPhrase("asil kaptan","asil kız")+". Bana yaptıklarını asla unutmayacağım.";
			link.l1 = "İyi yolculuklar o zaman. Elveda...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_238":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			if(pchar.GenQuest.EncGirl == "EncGirlFack_GetMoney") 
			{
				AddSimpleRumour(RandPhraseSimple("Have you heard? A whore was trying to sneak on board of a ship without documents, but she was caught and taken back to the brothel. They say she owed the madam quite a sum.",  
				"Have you heard? A whore without documents was caught at the port. They say she had cleaned out madam's coffers before attempting to flee from the brothel. I say, that source of filth and thievery must have been closed off long ago. Our kids are even seeing this and what can they learn from such an example?"), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_250":
			dialog.text = "Hayatımı mahvetme, kaptan! Babam beni o tefeci herifin oğluyla evlendirmek istiyor, o pis süt çocuğuyla... Sırf babasının kasasında bir servet var diye! İnan, onunla bir ömür geçireceğime, ormanda vahşi hayvanlara yem olmayı tercih ederim!";
			link.l1 = "Evliliğinizde ne sorun var, "+GetSexPhrase("güzellik","tatlım")+"? Sana talip olanı bırakma, onunla mutlu ol. Zaman geçince o süt çocuğuyla evlendiğine sevinebilirsin, ama iş işten geçmiş olabilir...";
			link.l1.go = "Node_251";
		break;
		
		case "Node_251":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "Hayır! Hayır, kaptan, ben seviyorum "+pchar.GenQuest.EncGirl.sLoverId+" ve başka bir adamla evlenmeyeceğim! Babam ise hiçbir şey duymak istemiyor! Diyor ki "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+" burada sadece bir misafir, bu yüzden burada asla iş bulamayacak, yoksulluk içinde ölmeye mahkûm, ben de onunla birlikte! Ve ben onun yanında olabilmek için dünyanın öbür ucuna bile giderim! Ne olur, beni ona götür, yalvarıyorum sana!";
			link.l1 = "Pekala, hadi gidelim. Sanırım seninle ne yapacağımı yol üzerinde çözerim...";
			link.l1.go = "Node_252";
		break;
		
		case "Node_252":
			Diag.TempNode = "Node_253";
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "9");
			AddQuestUserData("JungleGirl","sText", pchar.GenQuest.EncGirl.FatherGen);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId); 
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_253":
			Diag.TempNode = "Node_253";
			dialog.text = "Kaptan, beni yerleşim yerine götüreceğine söz vermiştin "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+".";
			link.l1 = RandPhraseSimple("Hatırlıyorum.","Merak etme, seni oraya götüreceğim.");
			link.l1.go = "exit";			
		break;
		
		case "Node_260":
			chrDisableReloadToLocation = false;
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Teşekkür ederim, "+GetSexPhrase("kapitan","genç hanımefendi")+", bir kez daha. Gerçekten, sana çok minnettarım.","Çok teşekkür ederim, "+GetSexPhrase("kaptan","genç hanım")+". Senin yardımın olmasaydı ne yapardım hiç bilmiyorum.");
				link.l1 = RandPhraseSimple("Bu sana ders olsun. Peki, bol şans...","Bir dahaki sefere daha dikkatli olmalısın... Şimdi evine koş, yapacak işlerim var.");
				link.l1.go = "Node_260End";
				link.l2 = "Nasıl bu kadar dikkatsiz olabilirsin? Neden tek başına ormana girdin?";
				link.l2.go = "Node_13";
			}
			else
			{
				dialog.text = "Oh, "+GetSexPhrase("kaptan","genç hanım")+", gerçekten sana nasıl teşekkür edeceğimi bilmiyorum.";
				link.l1 = "Önemli değil. Her zaman yardımcı olmaktan mutluluk duyarım...";
				link.l1.go = "Node_261";
			}
		break;
		
		case "Node_260End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");			
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_261":
			dialog.text = "Beni meyhaneye götürebilir misin? Teyzemi beklemem ve biraz dinlenmem lazım, bu 'macera' bütün enerjimi aldı...";
			link.l1 = "Hayır, "+GetSexPhrase("güzellik","tatlım")+", bu benim için fazlasıyla yeterli. Yapacak çok işim var.";
			link.l1.go = "Node_262";
			link.l2 = ""+GetSexPhrase("Ah, kadınlar! Bir erkeğin yardımı olmadan yapamayacakları bir şey var mı acaba?","Neden bu kadar çaresizsin?")+" Hadi gidelim...";
			link.l2.go = "Node_263";
		break;
		
		case "Node_262":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_263":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";					
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
				
		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if(makeint(Pchar.reputation.nobility) >= 80)
			{
				dialog.text = "Biraz param var... Lütfen, minnettarlığımın bir göstergesi olarak kabul edin!";
				Link.l1 = "Teşekkür ederim. Bir dahaki sefere daha dikkatli ol lütfen.";
				Link.l1.go = "exit";
			}
			else 
			{
				if(hrand(1) == 0)
				{
					dialog.text = "Senin beni kurtardığını herkese anlatacağım! Herkes bilsin, "+GetSexPhrase("ne kadar cesur ve yürekli bir adamsın","ne kadar cesur ve yürekli bir hanımsınız")+"!";
					Link.l1 = "Teşekkür ederim.   Şimdi eve gitmelisin.";
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, makeint(PChar.rank)*100);
					dialog.text = "Biraz param var... Lütfen, minnettarlığımın bir göstergesi olarak kabul edin!";
					Link.l1 = "Teşekkürler. Bir dahaki sefere daha dikkatli ol.";
					Link.l1.go = "exit";
				}
			}
		break;

		case "ThanksAgain":
            Diag.TempNode = "ThanksAgain";
            dialog.text = "Herkese beni kurtardığını anlatacağım! Herkes bilsin, "+GetSexPhrase("ne kadar cesur ve yürekli bir adamsın","ne kadar cesur ve yürekli bir hanımefendisiniz")+"!";
			Link.l1 = "Teşekkür ederim.   Şimdi eve gitmelisin.";
			Link.l1.go = "exit";
		break;
	}
}
