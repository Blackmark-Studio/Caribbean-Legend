// диалог прочих НПС по квесту Саги
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bir şey mi istiyorsun?";
			link.l1 = "Hayır, hiçbir şey.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//---------------------------------------------Джимми в доме в Марун-Тауне------------------------------------
		case "Jimmy":
			dialog.text = "Ne istiyorsun? Yas tuttuğumu görmüyor musun! Defol git, yoksa seni merdivenlerden aşağı tekmelerim!";
			link.l1 = "O zaman kendine merdivenli daha büyük bir ev al. Sonra insanları merdivenden atmak üzerine konuşuruz, kahraman...";
			link.l1.go = "Jimmy_1_1";
			link.l2 = "Neden bu kadar üzgünsün, Jimmy? Eğer işin ucunda güzel bir kadın yoksa, ömrümün sonuna kadar bir damla rom içmeyeyim! Ancak bir kadın, senin gibi eski bir deniz kurdunu eski dostlarına böyle tehditler savurtacak hale getirebilir...";
			link.l2.go = "Jimmy_1_2";
		break;
		
		case "Jimmy_1_1":
			dialog.text = "Senden gibi titiz insanlardan nefret ediyorum! Pastanın en güzel dilimleri hep size kalıyor. Bana bir kendini beğenmişi öldürtmeye izin vermediler, öfkemin acısını senden çıkaracağım!";
			link.l1 = "...";
			link.l1.go = "Jimmy_fight";
		break;
		
		case "Jimmy_fight":
			DialogExit();
			AddDialogExitQuestFunction("Saga_Jimmy_fight");
		break;
		
		case "Jimmy_1_2":
			dialog.text = "Ne?! Seni tanıyor muyum? Hatırlamıyorum seni, kahretsin...";
			link.l1 = "Benim, "+pchar.name+"! Blueweld'de o küstah paltolu adamı neredeyse bağırsaklarını deşerken çok güzel vakit geçirmiştik. Adı neydi onun, unuttum gitti... Neyse, bir daha denizde karşılaşırsam korvetindeki topları da umursamam!";
			link.l1.go = "Jimmy_2";
		break;
		
		case "Jimmy_2":
			dialog.text = "Adı Arthur'du! Arthur Donovan, 'Arbutus' korvetinin kaptanı! Pis herif! Yani, onu cehenneme göndermeme ramak kaldığı konusunda bana katılıyorsun, öyle mi?";
			link.l1 = "Elbette! Hiç şansı yoktu, ama arkadaşların karıştı. Onları affet, seni bir deniz subayını öldürmekten dolayı asılmaktan kurtarmak istediler.";
			link.l1.go = "Jimmy_3";
		break;
		
		case "Jimmy_3":
			dialog.text = "Ah! Keşke bir gemim olsaydı! O herif Antigua yakınlarında kolayca izlenebilir... ha! Onu denizin dibine gönderirsen sana borçlanırım!";
			link.l1 = "Anlaştık, ha-ha! Bu arada, Rumba gerçekten tüm bu çileye değer mi?";
			link.l1.go = "Jimmy_4";
		break;
		
		case "Jimmy_4":
			dialog.text = "Elbette! Ondan daha iyisini hiç tanımadım. Ama bana sadece gülüp geçiyor. Herkes o denizkızını istiyor. Bazı denizciler gizlice bana söylediler, bizim Yakup da benim Rumba'ma tıpatıp benzeyen bir kız arıyormuş. O da onu istiyor! Şimdi onun emirlerini nasıl yerine getireyim?";
			link.l1 = "Sessiz ol dostum! Duvarların kulağı var... Peki sence Jackman neden Rumba'yı arıyor?";
			link.l1.go = "Jimmy_5";
		break;
		
		case "Jimmy_5":
			dialog.text = "Kesinlikle öyle! Henry the Hangman adında birini ve yirmi yaşlarında, sarı saçlı, mavi gözlü bir kızı arıyor. Belize'den Gladys Chandler adında biri de onun bakıcısı olmalı.";
			link.l1 = "Bekle! Gladys'in soyadı farklı. Ve o onun annesi!";
			link.l1.go = "Jimmy_6";
		break;
		
		case "Jimmy_6":
			dialog.text = "Jackman kurnazdır! Onu hazırlıksız yakalayamazsın! Bir süredir Rumba'nın peşindeydim ve Gladys'in tam yirmi yıl önce Sean McArthur'la evlendiğini öğrendim. Ondan önce de Belize'de yaşıyormuş. İlk kocasının adı Pete Chandler'mış. Zavallı Pete bir sarhoş kavgasında öldürülmüş. Söylenenlere göre, o zamanlar tombul Gladys'e gönül koyan McArthur'un parmağı varmış bu işte. Gladys kucağında bir bebekle dul kalmış. Çocuk da babasından çok geçmeden ateşli bir hastalıktan ölmüş. Ve sadece birkaç ay sonra, Gladys ve Sean Blueweld'e bir kız çocuğuyla gelmişler, güya McArthur'un kızıymış. Peki Gladys bu kadar kısa sürede nasıl tekrar doğum yapmış olabilir? Anlıyor musun?";
			link.l1 = "Başka birine bundan bahsettin mi?";
			link.l1.go = "Jimmy_7";
		break;
		
		case "Jimmy_7":
			dialog.text = "Henüz değil. Çeneni kapa yoksa... beni bilirsin!";
			link.l1 = "Evet, biliyorum. Dilin çok bozuk, herkese her şeyi anlatıyorsun. Rumba seni göndermekle haklıydı, geveze...";
			link.l1.go = "Jimmy_8_1";
			link.l2 = "Tabii! Ağzımı sıkı tutarım! Şimdi gitmem gerek. Hoşça kal, Jimmy.";
			link.l2.go = "Jimmy_8_2";
		break;
		
		case "Jimmy_8_1":
			dialog.text = "Ne... ne dedin sen?!";
			link.l1 = "Başka kimseye söyleyemeyeceksin...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_KillToJimmy_kino");
		break;
		
		case "Jimmy_8_2":
			DialogExit();
			AddDialogExitQuestFunction("Saga_Jimmy_DlgExit");
		break;
// <-- Джимми 
		
//-------------------------------------------корвет Донована, абордаж-----------------------------------------
		//Донован
		case "Donovan_abordage":
			PlaySound("Voice\English\saga\Artur Donovan.wav");
			dialog.text = "Vay canavar!";
			link.l1 = "Kendi kendinize mi konuşuyorsunuz, Bayım?! Rumba nerede?";
			link.l1.go = "Donovan_abordage_1";
		break;
		
		case "Donovan_abordage_1":
			dialog.text = "Ne Rumba'sı? Gemimde lakaplı serserilere yer yok. Burası İngiliz donanmasına ait bir gemi!";
			link.l1 = "Benimle aptal numarası yapma, Donovan. Kimi kastettiğimi gayet iyi biliyorsun. Kız nerede? Helen nerede? Cevap ver, pislik herif...";
			link.l1.go = "Donovan_abordage_2";
		break;
		
		case "Donovan_abordage_2":
			dialog.text = "Helen? Gemimi de kara fahişelerine yer yok, seni pislik!";
			link.l1 = "Karada fahişe yok mu? İnanması güç, çünkü tam şu anda biri karşımda duruyor... Sanırım konuşmamızın bir anlamı kalmadı. Geber, zavallı solucan!";
			link.l1.go = "Donovan_abordage_3";
		break;
		
		case "Donovan_abordage_3":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterDonovanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Takehelen = "true";//признак, что абордировали судно
		break;
		
		//наш матрос
		case "Tempsailor":
			dialog.text = "Kaptan, talimatınız üzerine tüm kamaraları ve ambarı aradık. Ambarın içinde zincirlenmiş bir kız bulduk...";
			link.l1 = "Ne alçak herif! Tam da düşündüğüm gibi... Kızı zincirlerinden kurtardın mı?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "Elbette, Kaptan. Güvenle geminize getirildi.";
			link.l1 = "Aferin! Onu kamarama götür, burada işimiz bitince onunla konuşmak istiyorum.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Emredersiniz, Kaptan!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
		break;
		//<-- абордаж корвета Донована
		
//----------------------------------------поиск Энрике Гонсалеса, Картахена----------------------------------
		//фальшивый Гонсалес №1, дом
		case "GonsalesA":
			dialog.text = "Bir şey mi istiyorsun?";
			link.l1 = "Merhaba, Cellat! Kaptan Butcher selamlarını gönderiyor.";
			link.l1.go = "GonsalesA_1_1";
			link.l2 = "Benim adım Charles de Maure. Señora Gonzales'in eski bir dostu adına onun oğlu Enrique'yi arıyorum. Sanırım o kişi sizsiniz...";
			link.l2.go = "GonsalesA_2_1";
		break;
		
		case "GonsalesA_1_1":
			dialog.text = "Ne oluyor be! Ben hiçbir Kasap'ı tanımıyorum!";
			link.l1 = "Hadi Henry. Jackman'ın korsanları neden peşinde, anlat bana, sana zarar vermeyeceğim.";
			link.l1.go = "GonsalesA_1_2";
		break;
		
		case "GonsalesA_1_2":
			dialog.text = "Yardım edin! Korsanlar! Cinayet!";
			link.l1 = "Kapa çeneni, aptal! Bağırıp çağırman yüzünden kasabanın yarısı buraya koşacak. Ha, istediğin bu mu?!";
			link.l1.go = "GonsalesA_1_fight";
		break;
		
		case "GonsalesA_1_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesA");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesA_2_1":
			dialog.text = "Hm... Efendim, yanılıyorsunuz. Ben yabancı bir ailede büyüdüm, öz annemi hiç hatırlamıyorum. Bakıcımın soyadını aldım. Annemin adını bilmiyorum ama Gonzales olduğundan şüpheliyim. Hakkımda soruşturabilirsiniz, buradaki eski sakinlerin hepsi söylediklerimi doğrular. Üvey babam tanınmış biriydi, kendi çocuğu olmadığı için bu evi ben miras aldım ve...";
			link.l1 = "Üzgünüm. Görünen o ki, yanılmışım. Hoşça kal.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesA_3_1";
			else link.l1.go = "GonsalesA_2_2";
		break;
		
		case "GonsalesA_2_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "17");
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesA_3_1":
			dialog.text = "Bence öyle değil.";
			link.l1 = "Affedersiniz?";
			link.l1.go = "GonsalesA_3_2";
		break;
		
		case "GonsalesA_3_2":
			dialog.text = "Biliyor musunuz, yakın zamanda kolonimize acımasızca korsanlar saldırdı. Sanırım bunu duymuşsunuzdur? Bu saldırı sonucunda sayısız insan zarar gördü. Ben yara almadan kurtuldum ama bana miras kalan işlerim şimdi zor günler geçiriyor. Bütün bu felaketin arkasındaki suçlu ise bu korsanların lideri, Charlie Prince adında bir alçak.";
			link.l1 = "Çok üzgünüm, ama bunun benimle ne ilgisi var?";
			link.l1.go = "GonsalesA_3_3";
		break;
		
		case "GonsalesA_3_3":
			dialog.text = "Ha-ha, şu masum kuzucuğa bir bak! Zararıma sebep olan sensin, o yüzden kayıplarımı karşılamanı öneriyorum. On beş bin peso ile yetineceğim. Ve senin evimde hiç bulunmadığını varsayacağım.";
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = "Ne kadar kinci insanlarsınız... Alın paranızı. Ve unutmayın, bu şehirde olduğumu biri öğrenirse, geri dönerim.";
				link.l1.go = "GonsalesA_3_4";
			}
			link.l2 = "On beş bin mi? Hm... Hayatının o kadar ettiğini sanmıyorum. Demek ki seni susturmak için kılıcımla işi bitirmek daha ucuza gelir.";
			link.l2.go = "GonsalesA_3_5";
		break;
		
		case "GonsalesA_3_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "171");
		break;
		
		case "GonsalesA_3_5":
			dialog.text = "Gardiyanlar! Korsanlar! Cinayet!";
			link.l1 = "Kapa çeneni, aptal!";
			link.l1.go = "GonsalesA_3_6";
		break;
		
		case "GonsalesA_3_6":
			DialogExit();
			iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 2;
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SpSold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, iTemp, true);         
				LAi_SetWarriorType(sld); 
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
			sld = GetCharacter(NPC_GenerateCharacter("SpOfficer", "off_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 25, 100, 100, "blade_13", "pistol6", "bullet", 150);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesAK");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		// <-- участвовал в событиях Картахены
		
		// фальшивый Гонсалес №2, улицы
		case "GonsalesB":
			PlaySound("Voice\English\citizen\Pirati v Gorode-08.wav");
			dialog.text = "Kılıcımı beğendiğini görüyorum. İstersen sana satabilirim. Çok bir şey istemem, bir yudum rom için can atıyorum ve cebim bomboş.";
			link.l1 = "Ve ben bunu neden isteyeyim ki? Orman Şeytanı sana selamını iletmemi istedi.";
			link.l1.go = "GonsalesB_1_1";
			if (sti(pchar.money) >= 1000)
			{
				link.l2 = "Evet, gerçekten güzel bir pala bu. Kaça?";
				link.l2.go = "GonsalesB_2_1";
			}
		break;
		
		case "GonsalesB_1_1":
			dialog.text = "Bana bunun yerine iki yüz peso verseydi daha iyi olurdu!";
			link.l1 = "Yani, Svenson'u tanıyor musun?";
			link.l1.go = "GonsalesB_1_2";
		break;
		
		case "GonsalesB_1_2":
			dialog.text = "Siktir git, Svenson'un da canı cehenneme, bırak şeytana gitsin. Orman şeytanı mı, deniz şeytanı mı, umurumda değil. Hasta bir adama pala alarak yardım etmeyeceksen, o palayı senin kıçına beleşten sokarım.";
			link.l1 = "Gerçekten mi? Bunu nasıl yapacağını görelim, pislik surat!";
			link.l1.go = "GonsalesB_1_fight";
		break;
		
		case "GonsalesB_1_fight":
			chrDisableReloadToLocation = true;
			DialogExit();
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesB");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesB_2_1":
			dialog.text = "Tecrübeli bir adama benziyorsun! Bin peso ve senin olur.";
			link.l1 = "Anlaştık!";
			link.l1.go = "GonsalesB_2_2";
		break;
		
		case "GonsalesB_2_2":
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(pchar, "blade_10");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "Cartagena'da böyle iki pala var - biri bende, diğeri fenerdeki yaşlı Alvares'te. Ama o kendi palasını satmaz. Tam bir ikiyüzlü, eski korsan kokusunu uzaktan alırım ben. O kılıç onun için bir tür tılsım.\nZavallı adam, keşke unutabilse dediği şeylere yanıyor belli ki. Her ay kiliseye gitmesinin sebebi de bu olsa gerek; uykusunu kaçıran günahları onu rahat bırakmıyor.";
			link.l1 = "Ve görüyorum ki senin de geçmişin var. Herhalde Svenson'un bahsettiği kişi sensin. Cartagena'da karşılaşırsak sana selamlarını iletmemi söyledi.";
			link.l1.go = "GonsalesB_2_3";
		break;
		
		case "GonsalesB_2_3":
			dialog.text = "Svenson mı? Hiç duymadım. Benim adım Enrique Gallardo. Ama eğer o Svenson bana bir şişe rom getirecekse, onun için Henry de olurum. İstediğin gibi seslen, yeter ki akşam yemeğine geç kalma demezsin. Peki, gidiyor muyuz?";
			link.l1 = "Bugün değil. Svenson uzakta, ama meyhane yakın. Cebin artık boş değil, o yüzden dikkatli ol, Enrique.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesB_3_1";
			else link.l1.go = "GonsalesB_2_4";
		break;
		
		case "GonsalesB_2_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "19");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesB_3_1":
			dialog.text = "Tam olarak doymadılar ama. Daha fazlasını istiyorum. Ve sen bana ödeyeceksin.";
			link.l1 = "Şaşkınım... Hayatını hiç mi önemsemiyorsun? Şehrin ortasında beni soymayı mı düşünüyorsun? Hem de silahını az önce bana kendin sattıktan sonra?";
			link.l1.go = "GonsalesB_3_2";
		break;
		
		case "GonsalesB_3_2":
			dialog.text = "Hayır, bana kendin ödeyeceksin. Ve nedenini biliyorsun, değil mi?";
			link.l1 = "Merak ettim, dinliyorum.";
			link.l1.go = "GonsalesB_3_3";
		break;
		
		case "GonsalesB_3_3":
			dialog.text = "Seni tanıdım. Ben dehanede, meyhanede çıkan sarhoş bir kavgadan dolayı zindandayken adamların hapishaneye daldı ve bütün gardiyanları biçti. Anahtarları olan gardiyanın cesedine ulaşmayı başardım ve kendimi sokaklara attım. Şehir yanıyordu, her yerde cesetler, kan ve barut dumanı... Tıpkı bir gemi baskınında olduğu gibi! Ve o dumanın arasından, valinin konutundan çıkarken seni gördüm. Şiir gibi, değil mi? Yo-ho-ho, merhaba, Charlie Prens!";
			link.l1 = "Böyle bağırmayı kes! Bildiklerini göz önünde bulundurursak, hele senin bana para sızdırmaya hiç kalkışmaman gerekirdi. Sana neler yapabileceğimin farkında mısın?";
			link.l1.go = "GonsalesB_3_4";
		break;
		
		case "GonsalesB_3_4":
			dialog.text = "Şimdi bir zamanlar soyduğun şehrin ortasındasın, elinden hiçbir şey gelmez. O halde şöyle yapacağız: Bana... diyelim ki, on bin peso veriyorsun, hemen şimdi. Sanırım bu bir ay için yeterli olur. Sonra yoluna bakarsın! İster sevgili Henry'ine, ister Svenson'a, ister başka bir şeytana... Ama vermezsen, sadece bağırmam yeterli, seni hemen işkence aletleriyle dolu özel bir odaya sürüklerler.";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Lanet olsun, al on binini ve gözümün önünden defol! Ve Tanrı korusun, seni bir daha görmeyeyim.";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "Yeter artık, bıktım bu işten. Silahın artık benim, yani hiç şansın yok, pislik.";
			link.l2.go = "GonsalesB_3_7";
			link.l3 = "Haha, iyisin! Biliyor musun? Şimdiye kadar başka birini çoktan karnından boğazına kadar doğramış olurdum. Ama senin gibi adamlara ihtiyacım var. Şöyle yapalım: Sana on bin peso veriyorum, 'Asılmış Adam'ını geri alıyorsun, üstüne her ay üç bin daha ekliyorum – içki için yeter – ve gemimde misafir oluyorsun.";
			link.l3.go = "GonsalesB_3_9";
		break;
		
		case "GonsalesB_3_5":
			dialog.text = "Pekala, pekala, zaten gidiyorum! Aramanda bol şans, Charlie Prens!";
			link.l1 = "...";
			link.l1.go = "GonsalesB_3_6";
		break;
		
		case "GonsalesB_3_6":
			AddMoneyToCharacter(pchar, -10000);
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "191");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		case "GonsalesB_3_7":
			dialog.text = "Gardiyanlar! Gardiyanlar!!! Bu Charlie Prince!!!";
			link.l1 = "Seni alçak!";
			link.l1.go = "GonsalesB_3_8";
		break;
		
		case "GonsalesB_3_8":
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			LAi_group_AttackGroup("Spain_citizens", LAI_GROUP_PLAYER);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "192");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
		break;
		
		case "GonsalesB_3_9":
			dialog.text = "Senin tayfana katılmamı mı öneriyorsun?";
			link.l1 = "Aynen öyle. Ama bu teklif bir kerelik. Ne diyorsun? Kabul et, yoksa karnını deşerim. Charlie Prince'i bu kadar kolay şantajla alt edebileceğini gerçekten sanmıyorsun, değil mi?";
			link.l1.go = "GonsalesB_3_10";
		break;
		
		case "GonsalesB_3_10":
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 && makeint(pchar.reputation.nobility) < 48)
			{
				dialog.text = "Lanet olsun! Charlie Prince bizzat bana tayfasında yer teklif ediyor! Kahretsin, kabul ediyorum! Kılıcımı ve on bin peso mu geri ver. Böyle olacağını hiç düşünmemiştim!";
				link.l1 = "Al bakalım. Ve çeneni kapa: bu şehirde kim olduğumu kimsenin bilmesine gerek yok, anlaşıldı mı?";
				link.l1.go = "GonsalesB_3_11";
				break;
			}
			if(makeint(pchar.reputation.nobility) > 47)
			{
				dialog.text = "Hayır. İyi bir kaptan olabilirsin, ama bana kalırsa biraz fazla gerginsin. Evet, bir zamanlar Kartagena'ya yaptığın cesur baskınla İspanyollara korku saldın – ama bütün bunları Marcus Tyrex'in yardımıyla başardın. Kendi başına dürüstçe yağma yapacak cesaretin yok. Hadi, parayı çıkar bakalım!";
			}
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
			{
				dialog.text = "Hayır. Şüphesiz nam salmış bir korsansın, ama kaptan olarak pek etkileyici görünmüyorsun. Koloniyi ancak Marcus Tyrex'in yardımıyla yağmalayabildin – tek başına harap bir şalopaya bile çıkmaya cesaret edemezsin. O yüzden parayı çıkar bakalım!";
			}
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Lanet olsun, al on binini ve gözümün önünden kaybol! Ve Tanrı korusun, seni bir daha görmeyeyim.";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "Yeter artık, bıktım bu işten. Silahın artık benim, bu yüzden hiç şansın yok, pislik.";
			link.l2.go = "GonsalesB_3_7";
		break;
		
		case "GonsalesB_3_11":
			dialog.text = "Anladım, aptal değilim.";
			link.l1 = "İyi.";
			link.l1.go = "GonsalesB_3_12";
		break;
		
		case "GonsalesB_3_12":
			DialogExit();
			AddMoneyToCharacter(pchar, -10000);
			LAi_RemoveLoginTime(npchar);
			npchar.quest.OfficerPrice = 3000;
			npchar.reputation.nobility = 30;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			npchar.loyality = MAX_LOYALITY;
			GiveItem2Character(npchar, "blade_10");
			EquipCharacterByItem(npchar, "blade_10");
			TakeItemFromCharacter(pchar, "blade_10");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			AddQuestRecord("Saga", "193");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
		break;
		// <-- участвовал в событиях Картахены
		
		//настоящий Гонсалес - Ортега, маяк
		case "Ortega":
			dialog.text = "Bugün de, başka bir gün de misafir beklemiyorum. Ne istiyorsun?";
			link.l1 = "Merhaba, Cellat. Orman Şeytanı beni gönderdi. Jackman’ın adamlarından önce seni bulmam iyi oldu. Adamları seni tüm Karayiplerde arıyor. Şanslısın Henry, doğduğun yeri sadece Svenson biliyor. Beni seni uyarmam için gönderdi.";
			link.l1.go = "Ortega_1";
		break;
		
		case "Ortega_1":
			dialog.text = "Şimdi anlıyorum... Demek ki Svenson hâlâ hayatta ve eski dostunu unutmamış. Onu ilk kez hasar görmüş bir brigantin güvertesinde acemi bir denizci olarak gördüğümden beri çok kan döküldü... Hayat çok hızlı geçti ve önümde fazla zaman kalmadı\nİnsanlardan uzak, denize yakın bu ıssız topraklarda doğal sebeplerle ölmek istiyordum. Ama Jackman Karayipler’e döndüyse, beni rahat bırakmayacak. Suç benim değildi ama efendisine borçluyum. Her neyse, şimdi bana kim inanır ki.\nÖlümden değil, acıdan korkuyorum. Ve Jackman acı hakkında çok şey bilir. Sadece bunu düşünmek bile kalbimi durduruyor, her şey kararıyor.";
			link.l1 = "Butcher yirmi yıl önce asıldı, yani artık kimseye borcunu ödemek zorunda değilsin. Eğer Jackman'dan korkuyorsan, borcunu bana devredebilirsin. Zaten er ya da geç onunla karşılaşacağını düşünüyorum.";
			link.l1.go = "Ortega_2";
		break;
		
		case "Ortega_2":
			dialog.text = "Butcher gibi adamları asmak kolay değildir. St. John'un eski celladı, cehennemden dönen ölüler hakkında sana ilginç hikâyeler anlatabilirdi. Jacob da kaptanından iyi ders aldı, bu yüzden en çok hangisinden korkmam gerektiğinden emin değilim.";
			link.l1 = "Jackman neden sana ihtiyaç duyuyor?";
			link.l1.go = "Ortega_3";
		break;
		
		case "Ortega_3":
			dialog.text = "Butcher'ın kızını koruduğu için bir dul kadına altın teslim etmem gerekiyordu. Neden bana öyle bakıyorsun? Evet, o doğduktan kısa bir süre sonra 'Neptune' batırıldı. Zamanında geri dönemediği için beni gönderdi; bebeğe ve bakıcısına göz kulak olmamı istedi.";
			link.l1 = "Bakıcı Gladys Chandler mıydı?";
			link.l1.go = "Ortega_4";
		break;
		
		case "Ortega_4":
			dialog.text = "Aptal numarası yapma. Eğer Jackman beni arıyorsa, demek ki Kasap'ın kızına ihtiyacı var. Belize'den Gladys adında bir kadını ve onun evlatlığını aradığını zaten biliyor olmalısın. Benimle dürüst olursan, belki sana güvenebilirim.";
			link.l1 = "Gladys'e ne söylemen gerekiyordu?";
			link.l1.go = "Ortega_5";
		break;
		
		case "Ortega_5":
			dialog.text = "Hiçbir şey. Ona Kasap'ın yüzüğünü göstermem gerekiyordu, böylece kaptanın gönderdiği bir ulak olduğumu anlayacaktı. Ayrıca bebeğin ihtiyaçları için ona bir sandık doblon vermem gerekiyordu. Yüzüğü almak için bir alçağı öldürmek zorunda kaldım. Bu yüzden Antigua'da kalışım bir ay daha uzadı.\nSonunda Belize'ye vardığımda ise Gladys çoktan gitmişti ve şehir İspanyollar tarafından yakılıp yağmalanmıştı. O, evini satıp yeni sevgilisiyle ve küçük Helen'le kaçmayı başarmış. Umarım ona iyi bakmıştır ve kızı çingenelere ya da bir geneleve satmamıştır.";
			link.l1 = "Kasabın kızının adı Helen'di, değil mi?";
			link.l1.go = "Ortega_6";
		break;
		
		case "Ortega_6":
			dialog.text = "Aynen öyle. Kasabın annesinin hatırası için. Eğer yaşayan ölülerden ve sana ölü gözlerle bakan korsanlardan korkmuyorsan, yüzüğü ve altını sana verebilirim. Hiç dokunmadım. Açlıktan ölüyordum ama yine de dokunmadım. Onlarla ne istersen yap. Karşılığında ise senden y...";
			link.l1 = "Ne oluyor, Henry?!";
			link.l1.go = "Ortega_7";
		break;
		
		case "Ortega_7":
			dialog.text = "Sen... s... ben so...r... oh!";
			link.l1 = "Hayır!";
			link.l1.go = "Ortega_8";
		break;
		
		case "Ortega_8":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			AddQuestRecord("Saga", "20");
			pchar.questTemp.Saga = "svenson1";
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "bucher_ring"); //перстень Бучера
			//таймер на возврат смотрителя
			SetFunctionTimerCondition("Saga_LightmanReturn", 0, 0, 10, false);
			//ставим прерывания, если ГГ наследил в городе
			if (CheckAttribute(pchar, "questTemp.Saga.Trap"))
			{
				pchar.quest.Saga_Trap.win_condition.l1 = "location";
				pchar.quest.Saga_Trap.win_condition.l1.location = "Mayak11";
				pchar.quest.Saga_Trap.function = "Saga_CreateTrapBandos";
				TraderHunterOnMap(true);
			}
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs");
			//pchar.questTemp.HelenDrinking = "end_henry";
		break;
		
		//бандиты в поисках Гонсалеса, маяк
		case "saga_trap":
			dialog.text = "A-ah, işte meraklı dostumuz geldi! Sonunda Gonzales'i buldun mu? Aferin, bizi ona getirdin... artık sana ihtiyacımız yok. Çocuklar, şu soytarıyı öldürün!";
			link.l1 = "Ölme vakti geldi, yengeç artıkları!";
			link.l1.go = "saga_trap_1";
		break;
		
		case "saga_trap_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			int n = makeint(MOD_SKILL_ENEMY_RATE/3);
			for (i=1; i<=3+n; i++)
			{	
				sld = characterFromId("sagatrap_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		//<-- поиск Гонсалеса, Картахена
		
//--------------------------------------------НПС по квесту Возвращение барона---------------------------------
		
		// доминиканский вождь
		case "DominicaHead":
			dialog.text = "U-ah! U-ah! Büyük Kukulcan yeni bir kurban istiyor! O-eh! Geçmişten kudretli bir savaşçının ruhu köyümüze, büyük Kukulcan'a kurban edilmek için geldi! O-eh! Herkes kudretli savaşçı ruhuna eğilsin!";
			link.l1 = "(kısık sesle) Ne oluyor, neredeyim ben?";
			link.l1.go = "DominicaHead_1";
			NextDiag.TempNode = "DominicaHead";
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A Comanche potion is used", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("You are feeling that your health is restored!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "DominicaHead_1":
			dialog.text = "O-eh! Büyük savaşçı, ulu Kukulcan tarafından yutulmak istiyor! Güneş doğuyor, gölgeler kısalıyor! Ulu Kukulcan yakında uyanacak! Seni ona götürüyoruz, ey kudretli savaşçı, ve ataların diyarında yolculuğun sürecek!";
			link.l1 = "(kısık sesle) Saçmalık... Yine Kukulcan mı? Hey, şef, barış için geldim! Ben buraya...";
			link.l1.go = "DominicaHead_2";
		break;
		
		case "DominicaHead_2":
			dialog.text = "O-eh! Büyük savaşçı, hemen Kukulcan'a kurban edilmek istediğini söylüyor. Ah, büyük savaşçı! Şimdi Kukulcan'a gidiyoruz ve onun gelişini bekliyoruz! Savaşçılar! Atalarımızın ruhunu Kukulcan'a götürmek bizim için büyük bir onur!";
			link.l1 = "(hafifçe) Aptal... Peki, onlarla gitmem gerekecek. Henüz bana saldırmamış olmaları iyi, bu halde kendimi savunamazdım...";
			link.l1.go = "DominicaHead_3";
		break;
		
		case "DominicaHead_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1_back", "Saga_DominicaDollyReload", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
			}
		break;
		
		case "DominicaHead_4":
			dialog.text = "Kukulcan'a geldik, büyük atalar ruhu. Yakında güneş batacak, gölgeler uzayacak ve Kukulcan bizi ziyaret edecek. Bekle, büyük savaşçı...";
			link.l1 = "(hafifçe) Şimdi anlıyorum, Kızılderili savaş şefi...";
			link.l1.go = "DominicaHead_5";
		break;
		
		case "DominicaHead_5":
			DialogExit();
			bDisableCharacterMenu = true;//лочим Ф2
			AddQuestRecord("BaronReturn", "7");
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_DominicaDollyWait", 5.0);
			pchar.questTemp.Saga.BaronReturn = "third_teleport";
		break;
		
		case "DominicaHead_6":
			dialog.text = "Kukulcan yaşıyor! Kukulcan bizimle! Büyük savaşçı, Kukulcan’a kurban edilebilir! Savaşçılar, büyük atalar ruhunun önünde eğilin!";
			link.l1 = "(kısık sesle) Uzak dur, Şef. Kendim hallederim. Bu ilk seferim değil...";
			link.l1.go = "DominicaHead_7";
		break;
		
		case "DominicaHead_7":
			DialogExit();
			bDisableCharacterMenu = false;//разлочим Ф2
			AddQuestRecord("BaronReturn", "8");
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
			}
		break;
		
//----------------------------------------НПС по квесту Искушение Барбазона----------------------------------
		// капитан рыболовного баркаса, стыривший шелк, море
		case "BarbCapBarkas":
			dialog.text = "Size nasıl yardımcı olabilirim, Mösyö?";
			link.l1 = "Pekâlâ, pekâlâ...  söyle bakalım dostum, burada ne yapıyorsun?";
			link.l1.go = "BarbCapBarkas_1";
		break;
		
		case "BarbCapBarkas_1":
			dialog.text = "Ben burada ne yapıyorum? Balıkçıyım ve burada balık tutuyorum. Ve sen de bana bu ses tonuyla ne diye hesap soruyorsun, anlamadım?";
			link.l1 = "Bana yalan söyleme, dostum. Belki gerçekten balıkçısındır, ama burada balık tuttuğun yok. Tam da bu noktada değerli gemi ipeği denize atıldı. Ve senin burada olman bana fazlasıyla şüpheli görünüyor.";
			link.l1.go = "BarbCapBarkas_2";
		break;
		
		case "BarbCapBarkas_2":
			dialog.text = "Ne saçmalık bu? Hangi ipekten bahsediyorsun sen?";
			link.l1 = "Hangi ipek? Çin ipeği... Aptal numarası yapma! Şimdi beni iyi dinle: ya hemen ambarından ipeği çıkarıp bana verirsin, ya da ben kendim alırım. Ama önce, adamlarım seninle ve tayfanla ilgilenecek. Ne diyorsun? Adamlarımı çağırayım mı?";
			link.l1.go = "BarbCapBarkas_3";
		break;
		
		case "BarbCapBarkas_3":
			dialog.text = "Hayır! Efendim, bilmiyordum... O balyalar öylece etrafta yüzüyordu, ben de...";
			link.l1 = "İpeği gemime getir. Acele et!";
			link.l1.go = "BarbCapBarkas_4";
		break;
		
		case "BarbCapBarkas_4":
			dialog.text = "Evet, evet, tabii ki. Hemen hallederiz, yeter ki kayığımı alma!";
			link.l1 = "Kımılda biraz! Fazla vaktim yok...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_BarbBarkasSilk");
		break;
		
		case "BarbCapBarkas_5":
			dialog.text = "İşte, bulduğumuz her şeyi getirdik - tam dokuz balya. Hepsi bu kadar, yemin ederim...";
			link.l1 = "Pekâlâ. Balık tutmaya devam edebilirsin, ama bir daha başkalarının eşyalarına göz dikme!";
			link.l1.go = "BarbCapBarkas_6";
		break;
		
		case "BarbCapBarkas_6":
			DialogExit();
			npchar.DontDeskTalk = true;
			npchar.lifeday = 0;
			LAi_SetStayType(npchar);
			pchar.quest.BarbBarkas_Sink.over = "yes"; //снять прерывание
			pchar.quest.BarbBarkas_Abordage.over = "yes"; //снять прерывание
			NextDiag.CurrentNode = "BarbCapBarkas_7";
			AddQuestRecord("BarbTemptation", "6");
			pchar.questTemp.Saga.BarbTemptation = "give_silk";
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "BarbCapBarkas_7":
			dialog.text = "İstediğini zaten aldın. Bende başka bir şey kalmadı! Daha ne istiyorsun?";
			link.l1 = "Sakin ol dostum. Gidiyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BarbCapBarkas_7";
		break;
		
		// Моррель, капитан потопленного судна, тюрьма
		case "Morelle":
			dialog.text = "Eğer seni Barbazon gönderdi ise, ona söyle ki ben bu hapishaneden kendi isteğimle çıkmak istemiyorum. Duruşmayı beklemeyi tercih ederim. Boynuma dolanacak Hollanda ipi bile onun iyiliğinden daha iyidir.";
			link.l1 = " Acele etme. Seyrüsefercin Jacques'a öldüğünü söylemiş. Beni denize attığın ipeği bulmam için gönderdi. Brigantininde ne kadar ipek vardı?";
			link.l1.go = "Morelle_1";
		break;
		
		case "Morelle_1":
			dialog.text = "Benim suçumdu, kahretsin. Kurye Barbazon için dokuz balya ipek getirdi. Onu takip etmelerini emrettim. Gürültü çıkardı, bu yüzden boğazını kesmek zorunda kaldık. Kendi gizli yerinde fazladan üç balya daha vardı, onları kendime aldım ve kendi sakladığım yere gizledim. Ama galiba istemediğimiz dikkatleri üzerimize çektik.\nBizi çabucak buldular ve açık denizde 'Salt Dog'u bekleyen bir Hollanda devriyesi vardı. Kaçmayı başaramadık. Eğer Barbazon'a benden bahsetmezsen, ipeği kendine alabilirsin. Sakladığım yer Grand Case Plajı'nda, çıkmazın oradaki taşların arasında. Bir daha ihtiyacım olacağını sanmıyorum.";
			link.l1 = "Pekala. Barbazon'a hâlâ hayatta olduğunu söylemeyeceğim. Onun hakkında söylenenler doğruysa, Hollandalılar tarafından asılman senin için daha iyi olur. Ya da belki şansın yaver gider de seni kürek mahkûmluğuna çarptırırlar.";
			link.l1.go = "Morelle_2";
		break;
		
		case "Morelle_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			// тайник - модель
			//int m = Findlocation("Shore40");
			//locations[m].models.always.Roll = "Roll_of_rolls";
			//Locations[m].models.always.Roll.locator.group = "quest";
			//Locations[m].models.always.Roll.locator.name = "quest1";
			pchar.quest.Saga_MorelGoods.win_condition.l1 = "locator";
			pchar.quest.Saga_MorelGoods.win_condition.l1.location = "Shore40";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator_group = "quest";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator = "quest1";
			pchar.quest.Saga_MorelGoods.function = "Saga_SetMorelGoods";
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
		
		// Валет, брат Джекмана в Капстервиле
		case "valet":
			dialog.text = "Beyaz köpekbalığı avının ne zaman başlayacağını bilen adamı bekliyorum.";
			link.l1 = "Av başladı.";
			link.l1.go = "valet_1";
		break;
		
		case "valet_1":
			dialog.text = "Sonunda! Şimdi dikkatlice dinle. La Vega'da Marcus Tyrex'i bulup ona 'Separator' adlı brigantinin Turks Adası yakınlarında saldırıya uğradığını ve şu anda Güney Koyu'nda saklandığını söylemelisin. Geminin kaptanı ağır yaralı ve mürettebat yardım bekliyor. Sen 'Separator'dan bir denizciyi aldın ve sana her şeyi anlattı. Şimdi o öldü. Bildiğin tek şey bu. Anladın mı?";
			link.l1 = "Ve bunun için neden bana ihtiyacın var? Sırf bunun için mi bu kadar bekledim...";
			link.l1.go = "valet_2";
		break;
		
		case "valet_2":
			dialog.text = "Senin işin soru sormak değil, sana verilen işi yapmak. Ama haklısın, seni uyarmam gerek: Tyrex, doğruyu söylediğinden emin olana kadar seni bırakmaz. Fakat her şeyi öğrendiğinde, iyi bir ödeme alırsın. Tabii eğer bunu yapabilecek durumda olursa...";
			link.l1 = "Beni kandırıyorsun, Bayım... Neden onun teşekkürünü kendin almak istemiyorsun?";
			link.l1.go = "valet_3";
		break;
		
		case "valet_3":
			dialog.text = "Caramba! Meraklı hallerini hiç sevmiyorum! Bu gevezeliğin seni bir gün erkenden mezara sokacak.";
			link.l1 = "Evet, bazen gerçekten çekilmez olabiliyorum. Özellikle de birinin bana kazık atmaya çalıştığını sezdiğimde. Yok dostum, şimdi benim kurallarımla oynayacağız. Kim senin patronun, kahretsin? Söyle, yoksa seni konuştururum!";
			link.l1.go = "valet_4";
		break;
		
		case "valet_4":
			dialog.text = "Sen... alçak herif! Barbazon bunun hesabını soracak ve senin hayatın burada sona erecek, pislik!";
			link.l1 = "Ha! Bunu bekliyordum. Hazır ol, alçak!";
			link.l1.go = "valet_5";
		break;
		
		case "valet_5":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_ValetDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "vensan":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				dialog.text = "Charlie Prince? Ne yapıyorsun burada? A-ah, kahretsin, demek sendin! Bütün bunlar senin yüzünden oldu!";
				link.l1 = "Sakin ol, Bernie. Senin tarafındayım. Pusu ortadan kaldırıldı, sen ve gemin güvendesiniz.";
				link.l1.go = "vensan_8";
			}
			else
			{
				dialog.text = "Sen kimsin, lanet olsun? Buraya nasıl geldin? Hemen git, gemim patlayıcılarla dolu ve kıyıdaki alçaklar tek bir atışla havaya uçurabilirler.";
				link.l1 = "Endişelenmeyin, Bayım. Sahildeki pusu ortadan kaldırıldı. Geminiz artık güvende, tabii güvertede pipo yakmadığınız sürece. Adınız nedir?";
				link.l1.go = "vensan_1";
			}
		break;
		
		case "vensan_1":
			dialog.text = "Vincent. Bernard Vincent. Peki senin adın ne?";
			link.l1 = "Kaptan "+GetFullName(pchar)+". Bu ipleri keseceğim ve seni özgür bırakacağım...";
			link.l1.go = "vensan_2";
		break;
		
		case "vensan_2":
			LAi_SetStayType(npchar);
			dialog.text = "Oh... minnettarım. Size nasıl teşekkür edebilirim?";
			link.l1 = "Henüz bitmedi, efendim. Mürettebatınızdan hâlâ hayatta olan var mı?";
			link.l1.go = "vensan_3";
		break;
		
		case "vensan_3":
			dialog.text = "Adamlarımın üç düzinesi ambar bölümüne kilitlendi...";
			link.l1 = "Onları serbest bırak ve hemen buradan uzaklaş. ";
			link.l1.go = "vensan_4";
		break;
		
		case "vensan_4":
			dialog.text = "Ama...";
			link.l1 = "Vakit kaybetme, Bernard. Bana sonra La Vega'da teşekkür edersin... Tyrex de bana teşekkür edebilir.";
			link.l1.go = "vensan_5";
		break;
		
		case "vensan_5":
			dialog.text = "Yani, buraya tesadüfen gelmedin mi? Her şeyi biliyor muydun?";
			link.l1 = "Evet, biliyordum. Jackman'ın planını ve Marcus'u öldürme niyetini ortaya çıkarmayı başardım. Ha, Tyrex'e yerinde oturmasını söyle, karışıklığı Jackman'ı kaçırabilir.";
			link.l1.go = "vensan_6";
		break;
		
		case "vensan_6":
			dialog.text = "Ona mutlaka söyleyeceğim! Şimdi mi gidiyorsun?";
			link.l1 = "Evet. Sen de acele etmelisin.";
			link.l1.go = "vensan_7";
		break;
		
		case "vensan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto2", "none", "", "", "", 5.0);
			Ship_SetTaskRunaway(SECONDARY_TASK, GetCharacterIndex("Cap_Vensan"), GetMainCharacterIndex());
			pchar.questTemp.Saga.BarbTemptation.Vensan_free = "true";
			if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.vensan_attack"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = characterFromId("Mary");
				else sld = characterFromId("Helena");
				sld.dialog.currentnode = "sea_bomb"; 
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			sld = characterFromId("Cap_Vensan");
			sld.lifeday = 1;
			sld.DontDeskTalk = true;
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "vensan_8":
			dialog.text = "Gerçekten mi? Bak, üzgünüm kardeşim...";
			link.l1 = "Boşver. Sadece iplerini keseyim ve seni serbest bırakayım.";
			link.l1.go = "vensan_9";
		break;
		
		case "vensan_9":
			LAi_SetStayType(npchar);
			dialog.text = "Siktir... Ellerimi hissedemiyorum...";
			link.l1 = "Bernie, gemide başka sağ kalan var mı?";
			link.l1.go = "vensan_10";
		break;
		
		case "vensan_10":
			dialog.text = "Oturma bölümünde otuz adam kilitli...";
			link.l1 = "Bırak onları ve defol buradan. Hemen!";
			link.l1.go = "vensan_11";
		break;
		
		case "vensan_11":
			dialog.text = "Ama...";
			link.l1 = "Hemen La Vega'ya yelken aç. Marcus'a bu karmaşanın her ayrıntısını eksiksiz anlat.";
			link.l1.go = "vensan_12";
		break;
		
		case "vensan_12":
			dialog.text = "Markus seni mi gönderdi?";
			link.l1 = "O yapmadı. Bir alçağın planını ortaya çıkardım. Bu entrikayla Marcus'u ortadan kaldırmayı düşünüyordu. Şimdilik yerinde kalsın ve karışmasın, olur mu... Ona her şeyi sonra kendim anlatacağım. Ve lütfen, bana kızmayı bırakmasını da söyle.";
			link.l1.go = "vensan_7";
		break;
		
 //--------------------------------------НПС по Завещанию Шарпа--------------------------------------------------
		// Устрица, Поль Моллиган
		case "molligan":
			dialog.text = "Gemimde ne istiyorsunuz, beyefendi?";
			link.l1 = "İyi günler, Paul. Adın Paul Molligan, değil mi?";
			link.l1.go = "molligan_0";
		break;
		
		case "molligan_0":
			dialog.text = "Evet, benim. Size nasıl yardımcı olabilirim?";
			link.l1 = "Benim adım "+GetFullName(pchar)+" ve Jan Svenson beni gönderdi.";
			link.l1.go = "molligan_1";
		break;
		
		case "molligan_1":
			dialog.text = "Jan mı? A-ah, seni hatırlıyorum. Tabii ki! Son zamanlarda onun evine sık sık uğruyorsun. Peki, Jan benden ne istiyor?";
			link.l1 = "Blueweld'den ayrılmak için öyle acele ettin ki. Jan, gemine fazladan iki yüz kantar maun yükleyip onları Bridgetown'daki Lord Willoughby'ye teslim etmeni istedi. Gemini hazırla, adamlarım maunu ambarına yerleştirecek.";
			link.l1.go = "molligan_2";
		break;
		
		case "molligan_2":
			dialog.text = "Maun mu? Bunu Jan mı söyledi? Hm. Peki, neden kendin Barbados'a götürmüyorsun? Neden ben?";
			link.l1 = "Çünkü oraya sen gidiyorsun, ben değil. Svenson'dan acil bir görevim var, bu yüzden Bridgetown'a da gitmek için zaman kaybedemem. Ayrıca Jan, Lord Willoughby ile iş yapmam konusunda bana güvenmiyor ve bu işi senin halletmeni istiyor. Üzgünüm. Şimdi yüklemeye devam edelim, gitmem gerek.";
			link.l1.go = "molligan_3";
		break;
		
		case "molligan_3":
			dialog.text = "Bak, ambarımda hiç boş yer yok. Jan'ın benden istediğini yapamayacağım, isterdim ama.";
			link.l1 = "Yer yok mu? Garip... Jan bana burada boş yer olduğunu söylemişti.";
			link.l1.go = "molligan_4";
		break;
		
		case "molligan_4":
			dialog.text = "Doğru, ama Jan benim 'Oyster'a daha ağır toplar taktığımı bilmiyordu. Zaten alabildiğim kadar yük aldım, fazlasını yükleyemem. O yüzden keresteyi Barbados'a kendin götür, anlaştık mı dostum? Jan'a da söyle, ben götüremedim. Willoughby ile iş kolay: yanına git, yükü teslim et ve makbuzunu al. Bu kadar basit.";
			link.l1 = "Hm. Bu benim planım değildi... Ambarını bir kontrol edelim, ne dersin? Çarkçım eşyaları yerleştirme konusunda ustadır, malları ambarına sığdırır ve sana biraz boş yer bile bırakır...";
			link.l1.go = "molligan_5";
		break;
		
		case "molligan_5":
			dialog.text = "Dostum, daha fazla mal alamam. Toplarımı atıp 'Oyster'ı korumasız mı bırakayım?";
			link.l1 = "Pekâlâ, bu kadar eminsen... Ama Jan bundan hoşlanmayacak, aklında bulunsun!";
			link.l1.go = "molligan_6";
		break;
		
		case "molligan_6":
			dialog.text = "Bunu Svenson'a ben açıklarım, merak etme. Sonuçta onun suçu—gemimin tonajını bana sormadı.";
			link.l1 = "Eh, şimdi bu kütüklerle Barbados'a kadar yelken açmam gerekecek, kahretsin... Hoşça kal, dostum.";
			link.l1.go = "molligan_7";
		break;
		
		case "molligan_7":
			DialogExit();
			// ставим проверку скрытности
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > (10+hrand(50)))
			{
				pchar.questTemp.Saga.Molligan.friend = "true"; // будет шанс критического залпа картечью
				sTemp = "The scoundrel is still not suspecting a thing. I should get closer and shoot at him with grapeshot. A sudden strike will always win in any battle. ";
				log_Testinfo("Friends");
				AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
				AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			}
			else
			{
				pchar.questTemp.Saga.Molligan.enemy = "true"; // нападет
				sTemp = "";
				log_Testinfo("Enemies");
				AddCharacterExpToSkill(pchar, "Sneak", 150);//скрытность
			}
			AddQuestRecord("Testament", "7");
			AddQuestUserData("Saga", "sText", sTemp);
			NextDiag.CurrentNode = "molligan_8";
			npchar.DontDeskTalk = true; // patch-5
		break;
		
		case "molligan_8":
			dialog.text = "Anlaştık, değil mi?";
			link.l1 = "Evet, evet. Gemime gidiyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "molligan_8";
		break;
		
	//-----------------------------------------НПС по Теням прошлого--------------------------------------------
		// Джим Бенсон, плешивая мэгги
		case "benson":
			dialog.text = "Benden ne istiyorsun? Dedikoduya da kumara da merakım yok. Romumu da yalnız içerim. Üstelik, son seferimden sonra keyfim hiç yok.";
			link.l1 = "Ve son yolculuğunuzda ne gibi olağanüstü bir şey oldu?";
			link.l1.go = "benson_1";
		break;
		
		case "benson_1":
			dialog.text = "Bir iyi adam bana güvendi ve ben onu denize attım, çünkü mürettebatım bunu istedi.";
			link.l1 = "Ve suçu neymiş?";
			link.l1.go = "benson_2";
		break;
		
		case "benson_2":
			dialog.text = "Ben buraya yeni geldim ve burada pek kimseyi tanımıyorum. Bu yüzden geçmişini bilmeden o iyi kalpli, şişman adamı cerrah olarak tuttum. Barbados'tan ayrıldığımızdan beri peşimizde korsanlar var. Yumurtadan yeni çıkmış gemimi neden isterler ki?\nZar zor kurtulduk, şiddetli bir fırtına sayesinde. Bunu kutlamak için bir kadeh içtik. Ve o şişman budalanın aklına gelen en iyi şey, korsanların muhtemelen onun peşinde olduğunu, çünkü eskiden cellatlık yaptığını ve bilmemesi gereken şeyleri bildiğini herkese anlatmak oldu.\nTabii ki tayfam çok sinirlendi. Yani, gerçekten mi?! Gemide bir cellat, hem de cerrah olarak! Kimse de korsanlarla uğraşmak istemedi... O yüzden zavallı adamı karaya bırakmak zorunda kaldım. Hepsi onun suçu, ağzını tutamadı. Ama köylüye üzülüyorum, harika bir doktordu. Sadece bir dakikada akşamdan kalmalığımı geçirmişti.";
			link.l1 = "Kahretsin! Doktorunun adı Raymond Baker'dı, değil mi?";
			link.l1.go = "benson_3";
		break;
		
		case "benson_3":
			dialog.text = "Evet. Aynen öyle. Peki bunu nereden biliyorsun? Yoksa beni mi takip ediyordun?";
			link.l1 = "Hayır, o ben değildim. Sadece o adama ihtiyacım var, kendisi çok iyi bir doktor. Onu nereye çıkardınız?";
			link.l1.go = "benson_4";
		break;
		
		case "benson_4":
			dialog.text = "Kuzey enlemi 15 derece 28', batı boylamı 63 derece 28'. Acele edin, Bayım! Hâlâ yaşıyor olmalı ve onu kurtarırsanız suç benim üzerimden kalkacak!";
			link.l1 = "Demir alıyorum zaten!";
			link.l1.go = "benson_5";
		break;
		
		case "benson_5":
			DialogExit();
			NextDiag.CurrentNode = "benson_6";
			AddQuestRecord("Shadows", "3");
			npchar.lifeday = 0;
			bQuestDisableMapEnter = false;
			pchar.quest.Saga_Shadows_Baker.win_condition.l1 = "location";
			pchar.quest.Saga_Shadows_Baker.win_condition.l1.location = "Dominica";
			pchar.quest.Saga_Shadows_Baker.function = "Saga_SetBakerBoat";
			DeleteAttribute(pchar, "Cheats.SeaTeleport");
		break;
		
		case "benson_6":
			dialog.text = "Kaptan, acele et! Hâlâ hayatta olmalı!";
			link.l1 = "Evet, evet, geliyorum...";
			link.l1.go = "exit";
			NextDiag.TempNode = "benson_6";
		break;
		
	//---------------------------------------бандиты у джекмановского рудника-------------------------------
		case "mine_bandit":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Hey! Olduğun yerde kal! Kımıldama. Burası koruma altında!";
				link.l1 = "Çok sert olma, dostum! Arkadaşlar! Bizi Jackman gönderdi. Madene gitmemiz gerekiyor. Patronun emri...";
				link.l1.go = "mine_attack";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hey! Olduğun yerde kal! Kımıldama. Burası koruma altında!";
				link.l1 = "Hm. Ama geçmek istiyorum... Neden beni durduruyorsun, ne halt ediyorsun?";
				link.l1.go = "mine_bandit_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "A-ah, yine sen mi? Anlaşılan hâlâ anlamadın... Çocuklar, ateş edin!!";
				link.l1 = "...";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_bandit_0":
			dialog.text = "Hadi, devam et!";
			link.l1 = "Peki...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_bandit_0";
		break;
		
		case "mine_bandit_1":
			dialog.text = "Because the mine behind me is private property and I am here to stop any stranger like you from passing. You'd better turn around and leave this place, stranger. Our cannons are loaded with grapeshot; just one more step and you'll be turned into a wet puddle.";
			link.l1 = "Heh, anladım. Madenin iyi korunuyor. Peki, gidiyorum.";
			link.l1.go = "mine_bandit_exit";
			link.l2 = "Seni alçak! Bakalım sonunda kim bir su birikintisine dönecek!";
			link.l2.go = "mine_bandit_2";
		break;
		
		case "mine_bandit_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestReloadToLocation("Mine_02", "reload", "reload3", "");
		break;
		
		case "mine_bandit_2":
			dialog.text = "Sana bir şans verdim... Çocuklar, ateş edin!!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_bandit_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsFire", 1.5);
		break;
		
		case "mine_banditx":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Hey! Defol! Burası koruma altında!";
				link.l1 = "Hey, sakin ol dostum! Bizi Jackman gönderdi. Madene gitmemiz gerekiyor. Patronun emri...";
				link.l1.go = "mine_attackx";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hey! Defol! Burası koruma altında!";
				link.l1 = "Hm. Orada ne var?";
				link.l1.go = "mine_banditx_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "A-ah, yine sen mi? Anlaşılan hâlâ anlamadın... Çocuklar, ateş edin!!";
				link.l1 = "...";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_banditx_1":
			dialog.text = "Bu seni ilgilendirmez. Defol git yoksa vururuz, yemin ederim!";
			link.l1 = "Sakin ol. Gidiyorum.";
			link.l1.go = "mine_banditx_exit";
			link.l2 = "Seni alçak! Bakalım kim kimi vuracak!";
			link.l2.go = "mine_banditx_2";
		break;
		
		case "mine_banditx_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			DoQuestReloadToLocation("Mine_04", "reload", "reload3", "");
		break;
		
		case "mine_banditx_2":
			dialog.text = "Sana bir şans verdim... Tüfekler hazır! Ateş edin!!";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_banditx_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsxFire", 0.6);
		break;
		
		case "mine_attackx":
			dialog.text = "Gerçekten mi? O zaman parolayı biliyor olmalısın. Söyle bakalım, ama yalan söylüyorsan pişman olursun...";
			link.l1 = "Triton";
			link.l1.go = "mine_wrongx_password";
			link.l2 = "Neptune";
			link.l2.go = "mine_attackx_1";
			link.l3 = "Centurion";
			link.l3.go = "mine_wrongx_password";
			link.l4 = "Zıpkın";
			link.l4.go = "mine_wrongx_password";
		break;
		
		case "mine_attackx_1":
			dialog.text = "Doğru. Ama sen, dostum, buraya yanlış taraftan gelmişsin. Sana söylemediler mi? Geri dön ve kuru kuyudan sola giden yolu seç. Sonra tepeyi dolaş, orada ana kapıyı göreceksin.";
			link.l1 = "Buraya giremiyor muyum?";
			link.l1.go = "mine_attackx_2";
		break;
		
		case "mine_wrongx_password":
			dialog.text = "Adamlar, bir casus yakaladık! Tüfekler hazır! Ateş!!";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_attackx_2":
			dialog.text = "Hayır. Sadece ana girişten geçebilirsiniz.";
			link.l1 = "Pekâlâ, dostum... Hey! Bak! Surun tepesindeki o da ne böyle?";
			link.l1.go = "mine_attackx_3";
		break;
		
		case "mine_attackx_3":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mine_banditx_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			sld = characterFromId("Svensons_sold_12");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
			LAi_ActorAnimation(sld, "shot", "Saga_MineBanditxDie", 1.0);
		break;
		
		case "mine_attack":
			dialog.text = "Gerçekten mi? O zaman şifreyi biliyor olmalısın. Söyle bakalım, duymak istiyorum. Ve beni kandırmaya kalkarsan, bu hayatında yaptığın son şaka olur.";
			link.l1 = "Triton";
			link.l1.go = "mine_wrong_password";
			link.l2 = "Neptün";
			link.l2.go = "mine_attack_1";
			link.l3 = "Centurion";
			link.l3.go = "mine_wrong_password";
			link.l4 = "Zıpkın";
			link.l4.go = "mine_wrong_password";
		break;
		
		case "mine_attack_1":
			dialog.text = "Doğru. Devam et. Kampın başı, madenin girişinin solundaki evde. Git ve onunla konuş.";
			link.l1 = "Peki, dostum...";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_wrong_password":
			dialog.text = "Çocuklar, bir casus yakaladık! Toplar, ateş edin!!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_attack_2":
			DialogExit();
			locCameraFollowEx(true);
			NextDiag.CurrentNode = "mine_attack_3";
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetActorDialogAny2Pchar(npchar.id, "", 0.0, 0.0);
		break;
		
		case "mine_attack_3":
			dialog.text = "Başka ne var? Bir şeyi unuttun mu?";
			link.l1 = "Evet. Size en içten selamlarımı iletmem istendi.";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "Bana mı? Ha-ha! Kimden?";
			link.l1 = "Jan Svenson, seni alçak!";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			DialogExit();
			AddDialogExitQuestFunction("Saga_MineAttack");
		break;
		
	// ----------------------------- диалоги НПС при штурме бандитского рудника -------------------------------
		case "Svensons_off":
			dialog.text = LinkRandPhrase("Bu alçakları paramparça edeceğiz!","Bu pislikleri dövmek için sabırsızlanıyorum!","Jackman'ın adamlarının Batı Ana'da bulunmaya hiçbir hakkı yok! Onları buradan kovacağız!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_off";
		break;
		
		case "Svensons_sold":
			dialog.text = LinkRandPhrase("Savaşmaya hazırız!","Onlara göstereceğiz!","Kiminle uğraştıklarının farkında bile değiller!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_sold";
		break;
		
		case "gunner":
			PlaySound("Voice\English\evilpirates01.wav");
			dialog.text = "Komutanım, top hazır. Emrettiğiniz gibi bomba ile dolduruldu.";
			link.l1 = "Sanırım burada kimse bizi beklemiyor... Kendimizi tanıtmanın zamanı geldi. Jan bana kamplarının şu tepenin arkasında olduğunu söyledi. Oraya ulaşabilecek misin?";
			link.l1.go = "gunner_0_1";
		break;
		
		case "gunner_0_1":
			dialog.text = "Oldukça kolay, Komutanım. Varili biraz yukarı kaldıralım, bu yeterli olur... tamam.\nHazır olun!.. Ateş!!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "1";
		break;
		
		case "gunner_0_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_Gunfire", 3.0);
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_1":
			dialog.text = "";
			link.l1 = "Hm. Randolf, sence bir şeye mi çarptık? Fikrini duymak isterim.";
			link.l1.go = "gunner_1_1";
		break;
		
		case "gunner_1_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Komutanım, bir şeye ya da birine isabet ettik ama daha fazla ayrıntı veremem... şu lanet tepe görüşü kapatıyor. Açıyı değiştireceğim.\nHazır! Ateş!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "2";
		break;
		
		case "gunner_2":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			dialog.text = "Ha! Bakın, Komutan! Duman var! Kahretsin, galiba bir haydutun ahırını vurduk! Yaşasın-ah!";
			link.l1 = "Evet, dumanı görüyorum... Şüphesiz, şimdiden destansı bir zafer. Topu yeniden doldur ve patikaya nişan al, misafirlerimiz geliyor gibi görünüyor. Onları layıkıyla karşılayacağız!";
			link.l1.go = "gunner_2_1";
		break;
		
		case "gunner_2_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Emredersiniz, Komutan! Bombayı yükleyin! Top ekibi hazır! Fitil hazır! Benim komutumla ateş edin!";
			link.l1 = "...";
			link.l1.go = "gunner_2_2";
			npchar.quest.canonada = "3";
		break;
		
		case "gunner_2_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_01", 6.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_3":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			PlaySound("Voice\English\evilpirates05.wav");
			dialog.text = "Ha-ha, bu acıtmış olmalı!";
			link.l1 = "Daha rahatlama! Silahı doldur! Sanmıyorum ki yeterince aldılar. Daha fazlası geliyor!";
			link.l1.go = "gunner_3_1";
		break;
		
		case "gunner_3_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");//
			dialog.text = "Başüstüne, Komutan! Bir bomba yükleyin! Hazır! Benim komutumla ateş edin!";
			link.l1 = "...";
			link.l1.go = "gunner_3_2";
			npchar.quest.canonada = "4";
		break;
		
		case "gunner_3_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_02", 5.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_5":
			PlaySound("types\warrior04.wav");
			PlaySound("Voice\English\evilpirates06.wav");
			dialog.text = "Ha-ha-ha, alçaklar kaçıyor! Köpek eti bunlar! Bu mesafeden saçma onları parçalıyor! Görünen o ki, tekrar saldırmaya cesaretleri yok!";
			link.l1 = "Şimdi sıra bizde. Randolph, sen burada topun başında kalacaksın. Yola birkaç kez ateş et, sonra dumanı hedef al – inlerini yak! Yalnız bizi vurma.";
			link.l1.go = "gunner_5_1";
		break;
		
		case "gunner_5_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Başüstüne, Komutan! Topu hazırlayın! Mermi yükleyin!";
			link.l1 = "Adamlar! Silah başına! Peşimden gelin, saldırın! Yaşasın!!";
			link.l1.go = "attack";
		break;
		
		case "attack":
			DialogExit();
			n = Findlocation("mine");
			Locations[n].hidden_fire = true;
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\abordage_wining.wav");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			if (GetCharacterIndex("Svensons_sold_12") != -1 && pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=8; i++)
			{
				if (GetCharacterIndex("Ourmine_sold_"+i) != -1)
				{
					sld = characterFromId("Ourmine_sold_"+i);
					if (i == 1) sld.MusketerDistance = 10; 
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_NEITRAL);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_05Die");
			AddDialogExitQuest("MainHeroFightModeOn");	
			DoQuestCheckDelay("Saga_MineSetMusic", 0.3);
			// запускаем автобабахалку на 10 выстрелов
			iTotalTemp = 0;
			DoQuestCheckDelay("Saga_GunAutoFire", 7.0);
			bDisableCharacterMenu = false;//разлочим интерфейсы
			InterfaceStates.Buttons.Save.enable = true;//разрешим сохраняться
		break;
		
		case "convict":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = LinkRandPhrase("Bana zarar verme, ben onlardan değilim! Haydutları öldür!","Bizi kurtar, dostum! Ve hepsini öldür!","Kes onları, dostum, kes! Öldür hepsini!");
				link.l1 = "Ha! Merak etme, tam da şu anda bunu yapıyoruz.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Köleliğimiz bitti mi? Bizi özgür bırakacak mısın?","Heh, gerçekten bu günü görecek kadar hayatta kalabildim mi?","Alçaklar tüm kanımızı emdi....");
				link.l1 = "Bence yakında özgürlüğünün tadını çıkarabileceksin, dostum...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "convict";
		break;
		
		// жена Яна Свенсона
		case "js_girl":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Buradan gitmeniz daha iyi olur, efendim. Biz suçluları barındırmayız ve sömürge yetkilileriyle hiçbir sorun yaşamak istemeyiz.";
				link.l1 = "Pekala, gidiyorum...";
				link.l1.go = "exit";
				NextDiag.TempNode = "js_girl";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				// Первый диалог с Элен
				if(startHeroType == 4)
				{
					dialog.text = "Ah, Helen. Jan'ın karşısına çıkmadan önce biraz daha düzgün giyinebilirdin, ona gerçek yüzünü göstermek yerine. Ne yazık ki bana inanmıyor.";
					link.l1 = "Peki, ben tam olarak nasıl biriyim? O, çocukluğumdan beri büyümeme yardım etti ve beni herkesten daha iyi tanır. Ondan hiçbir şey saklamam. Bu sıcak havadan çocukluğumdan beri çok çektim, o yüzden bununla başa çıkmanın bir yolunu bulmam gerekti, hepsi bu.";
					link.l1.go = "js_helen_ft";
					NextDiag.TempNode = "js_girl";
					NPChar.quest.meeting = "1";
					break;
				}
				dialog.text = TimeGreeting()+", Efendim. Jan'ı görmek ister misiniz?";
				link.l1 = "Günaydın. Sizinle tanışmak güzeldi, Bayan?.. ";
				link.l1.go = "js_girl_1";
			}
			else
			{
				// заглушка элен
				if(startHeroType == 4)
				{
					dialog.text = "Jan içeride. Devam et, burada görecek bir şey yok, ayrıca sinirlerimi bozuyorsun.";
					link.l1 = "Zaten pek havamda değildim.";
					link.l1.go = "exit";
					NextDiag.TempNode = "js_girl";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Joan")) {
					dialog.text = "Grr!";
					link.l1 = "Size de iyi sağlıklar dilerim, Bayan Svensson.";
					link.l1.go = "exit";
					break;
				}
				
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
				{
					dialog.text = TimeGreeting()+", Kaptan "+GetFullName(pchar)+". Eğer Jan için buradaysan, seni hayal kırıklığına uğratacağım – burada değil. Önemli bir işi için gitti.";
					link.l1 = "Lanet olsun! Ona ihtiyacım var! Söyleyin bana Bayan Svenson, size ne zaman döneceğini söyledi mi?";
					link.l1.go = "js_girl_3";
					break;
				}
				dialog.text = "A-ah, yine sen, Kaptan "+GetFullName(pchar)+"... devam et, Jan her zamanki gibi yukarıda.";
				link.l1 = "Teşekkür ederim, Bayan Svenson...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_1":
			dialog.text = "Hanımefendi, Hanımefendi Johanna Svenson.";
			link.l1 = "Kaptan "+GetFullName(pchar)+".";
			link.l1.go = "js_girl_2";
		break;
		
		case "js_girl_2":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				dialog.text = "Kaptan? Sizi evimde ağırlamaktan memnuniyet duyarım. Ama eğer Jan için geldiyseniz, sizi hayal kırıklığına uğratacağım – burada değil. Önemli bir işi halletmek için gitti.";
				link.l1 = "Lanet olsun! Ona ihtiyacım var! Söyleyin bana Bayan Svenson, size ne zaman döneceğini söyledi mi?";
				link.l1.go = "js_girl_3";
				break;
			}
			dialog.text = "Kaptan? Sizi evimde ağırlamaktan memnuniyet duyarım. Eşim ikinci katta, çalışma odasında. Yukarı çıkın.";
			link.l1 = "Anladım, Bayan Svenson...";
			link.l1.go = "exit";
			NPChar.quest.meeting = "1";
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_3":
			dialog.text = "Hayır. Dönüşünün tam tarihini bile söylemedi, çünkü aramanın ne kadar süreceğini kendisi de bilmiyor.";
			link.l1 = "Rahatsız ettiğim için üzgünüm, ama ona gerçekten ihtiyacım var... Ne arıyor?";
			link.l1.go = "js_girl_4";
		break;
		
		case "js_girl_4":
			dialog.text = "Sana anlatayım. Güzel Helen, namıdiğer Rumba, rahmetli dostu Sean McArthur'un kızı, ortadan kayboldu. Jan bu genç şeytana öz kızıymış gibi davranır. Ona eski aşkını hatırlatıyor; aynı pervasız mizaca sahipti. En azından, Jan'ın ona olan ilgisinin sebebi bu, diye düşünüyorum. Her neyse, kız bir hafta önce 'Rainbow' adlı şilebi ve tüm mürettebatıyla birlikte kayboldu. Sean McArthur ona denizciliği öğretti, 'Rainbow' da vasiyetiyle ona geçti. Şimdi ise kaptan rolü oynuyor...";
			link.l1 = "Başına ne gelmiş olabilir?";
			link.l1.go = "js_girl_5";
		break;
		
		case "js_girl_5":
			dialog.text = "Kim bilir... Bir hafta o kadar uzun bir süre değil, ama McArthur'un dul eşi kızına bir şey olduğuna inanıyor ve Jan'ı da buna ikna etmeyi başardı. Adamlarını topladı ve onu kendi başına aramaya başladı, ama şimdiye kadar bir sonuç çıkmadı. Bence Helen gayet iyi ve Jan boş yere kendini yiyip bitiriyor.\nO yaşlı, şişman kadının saçmalıklarını fazla dinledi ve paniğe kapıldı. Büyük ihtimalle kız şu anda başka bir sevgilisiyle, meraklı gözlerden uzak, güvenli bir yerde eğleniyor. Karnı doyunca geri döner.";
			link.l1 = "Johanna, Gladys'i nerede bulabilirim? Onunla konuşmak istiyorum...";
			link.l1.go = "js_girl_6";
		break;
		
		case "js_girl_6":
			dialog.text = "Evi iskeleye yakın, solda. Ama muhtemelen orada değildir. Her gününü kalenin surlarında bekleyerek, kıymetli kızını arayarak geçiriyor.";
			link.l1 = "Anladım. Bilginiz için çok teşekkür ederim!";
			link.l1.go = "js_girl_7";
		break;
		
		case "js_girl_7":
			DialogExit();
			NextDiag.CurrentNode = "js_girl_8";
			sld = characterFromId("Gladis"); //устанавливаем Глэдис на форт
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "js_girl_8":
			dialog.text = "Jan henüz burada değil, Kaptan, bu yüzden sonra tekrar gelin.";
			link.l1 = "Anladım...";
			link.l1.go = "exit";
			NextDiag.TempNode = "js_girl_8";
		break;
		
		case "js_helen_ft":
			dialog.text = "You're always in heat, I'd say. You should go to church; I've barely ever seen you there.";
			link.l1 = "Vicdanım rahat - af dileyecek hiçbir şeyim yok. Hâlâ bana küskün müsün Joanna, çünkü gemime yardım etti de sana yeni bir elbise almadı?";
			link.l1.go = "js_helen_ft_1";
		break;
		
		case "js_helen_ft_1":
			dialog.text = "Ben mi? Kıskanç mı? Buna değmezsin. Sadece, her şey sana fazlasıyla kolay geliyor ve bunu hak etmiyorsun.";
			link.l1 = "Ama o gemiyi aldığım anda, kendi paramı kazanmaya başladım. O ise seni sokaktan bulup yanına aldı alalı, bir gün bile çalışmadın. O zaman asıl kim onun sırtından geçiniyor?";
			link.l1.go = "js_helen_ft_2";
		break;
		
		case "js_helen_ft_2":
			dialog.text = "Böyle konuşmaya devam edersen, günün birinde hak ettiğini bulacaksın. Jan ve Gladys sana biraz edep öğretmeliydi. Peki, hadi, ne diyeceksen de - ve gözümden kaybol, Helen. O içeride.";
			link.l1 = "Aptal tavuk. Tabii, hallederim.";
			link.l1.go = "exit";
		break;
		
		// хронометр Алекса
		case "Alexs_bandos":
			dialog.text = "Hey! Burada ne yapıyorsun?";
			link.l1 = "Ben de aynı şeyi sormak isterim – sen ve arkadaşların burada, benim zindanımda, ne yapıyorsunuz?";
			link.l1.go = "Alexs_bandos_1";
		break;
		
		case "Alexs_bandos_1":
			dialog.text = "Ha! Zindanı senin mi sandın? Ne zamandan beri senin oldu, seni zavallı?";
			link.l1 = "Babanın annenle yattığı o talihsiz gün.";
			link.l1.go = "Alexs_bandos_2";
		break;
		
		case "Alexs_bandos_2":
			dialog.text = "Belanı mı arıyorsun?";
			link.l1 = "Dinle dostum, sana buradan gitmen için son bir şans veriyorum. Burası benim zindanım ve kimsenin elini kolunu sallayarak içeri girmesine izin vermem, anladın mı? Sadece bir kez ıslık çalmam yeter, Isla Tesoro'nun yarısı bir dakika içinde burada olur.";
			link.l1.go = "Alexs_bandos_3";
		break;
		
		case "Alexs_bandos_3":
			dialog.text = "Pekâlâ, o zaman senin çeneni kapatmaya çalışacağız!";
			link.l1 = "Ha-ha! Zavallısın, pislik!";
			link.l1.go = "Alexs_bandos_4";
		break;
		
		case "Alexs_bandos_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Bermudes_Dungeon")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Alexs_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int iScl = 25+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Alexs_bandos_5", "mush_ctz_8", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", iScl*2+50);
			ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "AlexClock_BandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "helendrinking_gypsy":
			dialog.text = "Bir dakika bekle, şahin!";
			link.l1 = "Zamanlama pek iyi değil, tatlım.";
			link.l1.go = "helendrinking_gypsy_1";
		break;
		
		case "helendrinking_gypsy_1":
			dialog.text = "Ah, yanılıyorsun, yakışıklı. Bu kız senden hoşlanıyor, hem de hislerin karşılıklı olduğunu görebiliyorum.";
			link.l1 = "Pek iyi bir referans sayılmaz... Peki, ne istiyorsun? Sadaka mı?";
			link.l1.go = "helendrinking_gypsy_2";
		break;
		
		case "helendrinking_gypsy_2":
			dialog.text = "Sana bu zorlu işinde destek olmak istiyorum. Bak buraya! Büyülü bir kupa ve yasaklı bir merhem. Kupa sana içki konusunda yardımcı olur, merhem ise aşk meselelerinde. Hangisini seçersin? Sadece iki bin!";
			link.l1 = "Hiçbir şeye ihtiyacım yok - sizin gibiler için zaten bir yığın gümüş verdim.";
			link.l1.go = "helendrinking_gypsy_refuse";
			if (sti(pchar.money) >= 2000) {
				link.l2 = "Yasak merhem mi diyorsun? Pek aziz sayılmam, kabul. Ver bakalım şunu.";
				link.l2.go = "helendrinking_gypsy_fuck";
				link.l3 = "Bir kupa mı? Sarhoş gibi mi görünüyorum? Eh, kimi kandırıyorum ki... Alırım bir tane!";
				link.l3.go = "helendrinking_gypsy_drink";
			}
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_refuse":
			dialog.text = "Yakışıklı ama akılsız. Uç o zaman, şahin.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_drink":
			dialog.text = "Ah, saklama onu dipsiz ceplerinde! Uç git, şahini, ve günaha girme!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_01");
			Log_Info("Talisman 'Throat of cast iron' acquired!");
			PlaySound("interface\important_item.wav");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_fuck":
			dialog.text = "Oh, saklama onu dipsiz ceplerinde! Uç git, şahin, ve günaha girme!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_03");
			Log_Info("Talisman 'Cupid's Balm' acquired!");
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_joan":
			dialog.text = "Ah! Defol buradan, seni alçak! Kaç kere söyledim sana, evime gizlice girme diye! Ve bu da kim?";
			link.l1 = "Hanımefendi, biz zaten tanışıyoruz.";
			link.l1.go = "helendrinking_joan_1";
		break;
		
		case "helendrinking_joan_1":
			dialog.text = "Monsieur de Maure? Ne hoş! Kocamla böyle mi iş yapıyorsun?! Biliyordum! Jan'ı uyardım: bir gün bu kadın adamlarını yoldan çıkaracak dedim! Ve ellerinde ne var bakalım?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog1");
		break;
		
		case "helendrinking_joan_2":
			dialog.text = "Wha-a-a-at?! How dare you, wretch?! You're not going anywhere; my husband will be here any moment now and he'll teach you how to talk to the elders!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog3");
		break;
		
		case "helendrinking_fort_officer":
			dialog.text = "Burada neler oluyor? Bayan MacArthur! Babanıza büyük saygı duyardım, Bay Svensson da dostumuzdur... Ama geçen sefer her şeyin nasıl bittiğini unuttunuz mu?\nBu üzücü, bir subay sözü, gerçekten üzücü! Bizi davet edebilirdiniz!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog");
		break;
		
		case "helendrinking_fort_officer_1":
			dialog.text = "Misafirperverliğiniz için teşekkür ederim, Bayan MacArthur. Sizi tekrar aramızda görmekten hepimiz gerçekten memnunuz. Olanlar büyük bir sır, ama kasabanın bundan haberdar olması şaşırtıcı değil. Yine de, kimsenin dedikodu yapmayacağından emin olabilirsiniz. Kaptanlarımızdan birinin son zamanlardaki davranışları için içtenlikle özür dilerim. Ve özellikle size teşekkür etmek istiyorum, Bay de Maure.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog3");
		break;
		
		case "helendrinking_fort_officer_2":
			dialog.text = "Her şey yoluna girecek, Hanımefendi. Bay de Maure, açık konuşacağım – Donovan tam bir alçak ve haydut gibi davransa da, filo onu asla açıkça kınamayacak. Hatta büyük ihtimalle onu savunacaklar bile. Küçük seferiniz raporlara yansıdı ve ülkelerimiz arasındaki ilişkileri ciddi şekilde zorlaştırdı. Yine de, Bay Svensson'ın etkisi ve Capsterville'in size yaptığı dikkate değer tavizler göz önüne alındığında, korkacak hiçbir şeyiniz yok.";
			link.l1 = "Harika. Bence buna bir kadeh kaldırmalıyız!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog1");
		break;
		
		case "helendrinking_poorman":
			dialog.text = "Affedersiniz, peki iş hakkında ne düşünüyorsunuz?";
			link.l1 = "Hâlâ burada mısın?";
			link.l1.go = "helendrinking_poorman_1";
		break;
		
		case "helendrinking_poorman_1":
			dialog.text = "Sayın bayım, başka nereye gidebilirdim ki? Sadece biraz ihtiyaç gidermek için çıktım, duygusal sohbetinizi istemeden duydum ve biraz ısındım. Duygusal olarak, yani!";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.BoughtRainbow")) {
				link.l1 = "Aman Tanrım! Eh, sana söz verdiğim için yapacak bir şey yok. Git, komutayı devral.";
				link.l1.go = "helendrinking_poorman_bought";
			} else {
				link.l1 = "Sizin için bir işim yok, efendim.";
				link.l1.go = "helendrinking_poorman_notbought";
			}
		break;
		
		case "helendrinking_poorman_bought":
			dialog.text = "Emredersiniz, Kaptan!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helendrinking_poorman_notbought":
			dialog.text = "Ne yazık! Yine de ikram için teşekkürler, Kaptan!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helensleep_amelia_mary":
			dialog.text = "Baba, Oğul ve Kutsal Ruh adına... gir içeri, evladım.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "Merhaba, Rahibe Amelia. Sen de bana bağıracak mısın?";
				link.l1.go = "helensleep_amelia_mary_know";
			} else {
				link.l1 = "Kaybol! Bu nasıl bir kâbus? Neler oluyor? Rüya mı görüyorum?";
				link.l1.go = "helensleep_amelia_mary_notknow";
			}
		break;
		
		case "helensleep_amelia_mary_know":
			dialog.text = "Hayır, küçük şahini̇m. Ve Jan'ı affet – zavallı adam biraz sinirlendi. Ama evet, sana biraz kızmak istiyorum. Neden kiliseye geldin? Günahlarından arınmak için mi? Yoksa kızıl saçlı olanın peşinde miydin?";
			link.l1 = "Ben de kendimi bilmiyorum...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Sen de onu gördün mü? Gözüm ona takıldı.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_mary_notknow":
			dialog.text = "Kaybol. Zaten çoktan buluşmalıydık, ama her şeyi uzatıyorsun. Neden kiliseye geldin? Günahlarından arınmak için mi? Yoksa kızıl saçlı olanın peşinde miydin?";
			link.l1 = "Ben de kendimi bilmiyorum...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Sen de onu gördün mü? Gözüm ona takıldı.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen":
			dialog.text = "Günaydın, şahini̇m. Kabul henüz başlamadı, lütfen sırada bekleyin.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "Merhaba, Ekselansları. Siz de bana bağıracak mısınız?";
				link.l1.go = "helensleep_amelia_helen_know";
			} else {
				link.l1 = "Kaybol! Bu nasıl bir kâbus? Neler oluyor? Rüya mı görüyorum?";
				link.l1.go = "helensleep_amelia_helen_notknow";
			}
		break;
		
		case "helensleep_amelia_helen_know":
			dialog.text = "No, my falcon. And forgive Jan, the poor man got worked up. No need to scold you; you did everything right - didn't go after the red-haired one to the church. Good boy!";
			link.l1 = "Övülmek güzel bir şey. Özellikle de neden övüldüğünü açıkça bildiğinde.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Sen de onu gördün mü? Benim de dikkatimi çekti.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen_notknow":
			dialog.text = "Kaybol. Zaten çoktan buluşmamız gerekirdi, ama her şeyi uzatıp duruyorsun. Buraya gel, seni öveyim – kızıl saçlının peşinden kiliseye gitmedin. Aferin sana!";
			link.l1 = "Övülmek güzel bir şey. Özellikle de neden olduğunu açıkça bildiğinde.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Sen de onu gördün mü? O da benim dikkatimi çekti.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia":
			dialog.text = "Seni ayrıntılarla bunaltmayacağım, aptalım, ama şunu bil: büyük bir insan olacaksın. Çok kötülük getireceksin, ama çok daha fazla iyilik yapacaksın. Fakat mutluluk sana garanti edilmiyor. Mutluluk, şahinim, sadece kendi yolundan şaşmayanlara verilir. Ve sadık bir kadın, yolundan sapmaman için sana yardımcı olacak.\nİki kadın olacak hayatında, ikisi de mutluluk getirecek, ama sen sarışın olanı seçmelisin.";
			link.l1 = "Nedenmiş o? Buna kendim karar veririm!";
			link.l1.go = "helensleep_amelia_1";
		break;
		
		case "helensleep_amelia_1":
			dialog.text = "Elbette, kendin seç, ama sarışın olan daha iyi. Biz öyle karar verdik.";
			link.l1 = "Biz kimiz?";
			link.l1.go = "helensleep_amelia_2";
		break;
		
		case "helensleep_amelia_2":
			dialog.text = "Zavallı kız kendi gerçek adını bile bilmiyor. Söylersen, artık senin olur. Öyle derler.";
			link.l1 = "Artık hiçbir şey anlamıyorum.";
			link.l1.go = "helensleep_amelia_3";
		break;
		
		case "helensleep_amelia_3":
			dialog.text = "Kapıyı çalanı duydun mu? Aç kapıyı, sakın yanlış yapma.";
			link.l1 = "Gerçekten, biri kapıyı çalıyor... İçeri gel!";
			link.l1.go = "exit";
			
			PlaySound("interface\knock.wav");
			
			AddDialogExitQuestFunction("HelenSleep_WakeUp");
		break;
		
		case "helendrinking_notifier":
			dialog.text = "Monsieur, Bay Svensson sizden biraz zaman ayırmanızı rica etti.";
			link.l1 = "Lanet olsun, bu hiç iyiye işaret değil. Denerim ama söz veremem.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_End");
		break;
		
		case "islatesoro_pirate1":
			dialog.text = "Şanslı günümüz, çocuklar! Size demedim mi, er ya da geç buraya gelecekti? Peki güzelim, silahlarını ver ve bizimle gel.";
			link.l1 = "Yanlış anladınız, beyler. O benimle.";
			link.l1.go = "islatesoro_pirate1_1";
		break;
		
		case "islatesoro_pirate1_1":
			dialog.text = "Bu işe karışma, yoksa seni köpek gibi vururum. Kız için iyi bir ödül teklif edildi, biz de açız ve ilkesiziz.";
			link.l1 = "Benimle bu tonda konuşmaya devam edersen, açlık sorununu sonsuza dek çözerim.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroSpawnSecond");
		break;
		
		case "islatesoro_pirate1_2":
			dialog.text = "Akıl sağlığını mı yitirdin, Lucky? Onu ilk biz bulduk! Bana böyle saçma sapan laflar edecek kadar iyi bir sebebin olsa iyi olur!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog1");
		break;
		
		case "islatesoro_pirate1_3":
			dialog.text = "You're the rat here! We had just torn a big fat Spaniard apart; we can sit on our asses for a year!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog3");
		break;
		
		case "islatesoro_pirate2":
			dialog.text = "Bakın hele, kim gelmiş. Tamam, herkes dışarı, ve siz, hanımefendi, bizimle gelin.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog");
		break;
		
		case "islatesoro_pirate2_1":
			dialog.text = "Sayıca üstünüz ve senden daha sertiz, Dane. Başka ne sebep istiyorsun, pis fare? Altı aydır dişe dokunur bir ganimet görmedin, Vuazie'nin masasından kırıntı topluyorsun!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog2");
		break;
		
		case "islatesoro_pirate2_2":
			dialog.text = "";
			link.l1 = "Burada barışçıl bir çözüm olmayacak gibi görünüyor.";
			link.l1.go = "islatesoro_pirate_a";
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB")) {
				link.l2 = "Ne dedin? Şanslı mı? Onun ve Vuazie'nin sana sahte tüyolar vermek için işbirliği yaptığına dair bir söylenti duydum. Bu, denizdeki uğursuz şansını açıklıyor.";
				link.l2.go = "islatesoro_pirate_b";
			}
			bOk = (!CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice")) || (pchar.questTemp.Mtraxx.Retribution.Choice == "bad");
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC") && CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold") && bOk) {
				link.l3 = "Bu maskaralıktan bıktım artık. Isla Tesoro, beni dinleyin! Cartagena'da kimler yanımdaydı?! Mérida'yı kimlerle birlikte yaktık?! Bu sıçanlar bizzat Charlie Prince'e meydan okumaya cüret ediyor! Hadi gösterelim onlara, çocuklar!";
				link.l3.go = "islatesoro_pirate_c";
			}
		break;
		
		case "islatesoro_pirate_a":
			dialog.text = "Hâlâ buradasın mı, denizanası? Tamam çocuklar, hadi bakalım: kaptanı bağlayın, kızla sonra ilgileneceğiz, anlaşıldı mı?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog4");
		break;
		
		case "islatesoro_pirate_a_1":
			dialog.text = "Elbette, bari biraz kan dökelim. Hehe.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroA");
		break;
		
		case "islatesoro_pirate_b":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedB = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 60) {
				dialog.text = "Ne?! Kahretsin, o gözlüklü alçakla iş birliği yaptığını biliyordum! Hepinizi doğrayın çocuklar, kızı sonra alırız!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroB");
			} else {
				dialog.text = "Ne zırvalıyorsun Kaptan? Saygın insanlar iş konuşurken defol git buradan.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "islatesoro_pirate_c":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedC = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 50) {
				DialogExit();
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroC");
			} else {
				dialog.text = "Ne saçmalıyorsun Kaptan? Charlie Prince'i gördüm, sen onun yanında bir hiçsin. Saygın insanlar iş konuşurken kaybol buradan.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "francois":
			dialog.text = "Charles de Maure? Henri de Monpe'nin oğlu mu?";
			link.l1 = "Doğru, monsieur. Peki siz kimsiniz?";
			link.l1.go = "francois_1";
		break;
		
		case "francois_1":
			dialog.text = "Colonel Francois de Tavanne. You may consider this a direct challenge, monsieur; the gauntlet for the duel has been laid. I don't even wish to dirty my hands with you, but I swear, my blade will taste your blood!";
			link.l1 = "Bir düello mu? O halde, daha çok çabalamanız gerekecek, Albay. Şu anda, sizi ancak bir haydut sanabilirler, ve buralarda onlarla konuşmalar kısa sürer! Açıklayın kendinizi!";
			link.l1.go = "francois_2";
		break;
		
		case "francois_2":
			dialog.text = "Karımı baştan çıkardınız, monsieur! Ben kral ve vatan için kan dökerken, siz... siz karımla keyif çatıyordunuz!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog");
		break;
		
		case "francois_3":
			dialog.text = "Sessizlik, hanımefendi. Cesur kıyafetiniz herhangi bir kadının onurunu lekeliyor, gerçi bu soysuz kadın avcısının yanında size pek yakışıyor!";
			link.l1 = "Hâlâ düello için yeterli bir sebep yok, Albay. Ayrıca, burada da en az onun kadar onursuz davrandığınızı belirtmeme izin verin.";
			link.l1.go = "francois_4";
		break;
		
		case "francois_4":
			dialog.text = "Yeterli değil mi? Sordum – şu an yerimde bir düzine asil koca olabilirdi, efendim. Ama ayrıntıları istiyorsanız, utancımla itiraf ediyorum ki tutkularınızdan biri Lulu de Tavann’dı, en güzel ve en dürüst kadınlardan biri!";
			link.l1 = "Lulu, diyorsun... Peki, o nasıl?";
			link.l1.go = "francois_5";
		break;
		
		case "francois_5":
			dialog.text = "Sessizlik! Karım, senin çektirdiğin acılara daha fazla dayanamayarak kısa süre önce hayata gözlerini yumdu! Seni bulmak için neredeyse bir yıl ve bir servet harcadım, alçak! Yeter artık! Ya düelloyu kabul et, ya da seni bir köpek gibi öldüreceğim. Richard! Şahit ol buna!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog2");
		break;
		
		case "francois_6":
			dialog.text = "Sessizlik, bayım! Meydan okumayı kabul edin ya da sahip olduğunuz onurun son kırıntılarını da kaybedin!";
			if (pchar.HeroParam.HeroType == "HeroType_1") {
				link.l1 = "Bir düello, düellodur. Yalan söylemeyeceğim, bundan keyif alıyorum. Kaptan, Albay'a uygun bir tabut sipariş etme zamanının geldiğini iletin.";
			} else {
				link.l1 = "Dövüş mü istiyorsun? Alacaksın! Kaptan, Albay'a uygun bir tabut sipariş etme zamanının geldiğini ilet.";
			}
			link.l1.go = "francois_duel";
			link.l2 = "Burası Avrupa değil, Albay. Karayipler'de onur kazanmak daha zordur, ama kaybetmek de o kadar kolay değildir. Düellonuzu reddediyorum çünkü açıkçası istemiyorum.";
			link.l2.go = "francois_refuse";
		break;
		
		case "francois_7":
			dialog.text = "Baban zaten mezarın eşiğinde, alçak! Ve senin korkaklığını ona mutlaka bildireceğim!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog7");
		break;
		
		case "richard":
			dialog.text = "Albayım, düello hakkınızı onaylıyorum, ama sıradan haydutluğa izin vermem! Mösyö de Maure, ben Kaptan Richard Small. Albay de Tavannes'a gereken cevabı vermeye hazır mısınız?";
			link.l1 = "Bir dakika, Kaptan. Lulu’yu iyi tanırdım... ve o... sık sık hayran değiştirirdi, sağlığı da benden iyiydi... Nasıl öldü, Albay? Siz eve dönmeden önce mi, sonra mı?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog3");
		break;
		
		case "richard_1":
			dialog.text = "Lütfen, François, bana izin ver. Monsieur de Maure, size meydan okundu. Blueweld subaylar topluluğu, Albay de Tavannes'in hesaplaşma talebinin haklı olduğunu kabul ediyor. Meydan okumayı kabul edin ya da onurunuzu kaybedin.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog5");
		break;
		
		case "richard_2":
			dialog.text = "Charles, lütfen, burada centilmenleriz. Bu uygun değil. Albay seninle buluşmak için buralara kadar geldi! Bu tam bir rezalet!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog8");
		break;
		
		case "richard_3":
			dialog.text = "E-evet, elbette, hanımefendi. Ama ben...";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "helen");
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath1");
		break;
		
		case "richard_4":
			dialog.text = "Kaptan de Maure, bugün gün senin! Belki en düzgün dövüş olmadı ama bugün onurunu savundun.";
			link.l1 = "Bir şey mi dediniz, Kaptan? Bugünkü programıma bir düello daha sığdırabilirim.";
			link.l1.go = "richard_5";
		break;
		
		case "richard_5":
			dialog.text = "Özür dilerim, Kaptan. Sadece biraz gerginim!";
			link.l1 = "Bence artık burada bulunmana gerek yok.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory");
		break;
		
		case "richard_duel":
			dialog.text = "Adil bir karar! Gerçi en saygın şekilde ifade edilmedi... Beyler! Başlayalım!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuel");
		break;
		
		case "alonso":
			dialog.text = "Kaptan, bu soyluların kullandığı süslü lafların hepsini anlamıyor olabilirim, ama bakın, birine korkak dendi mi, genelde öylece bırakmazsınız. Adamı dövün, Kaptan, yoksa tayfa endişelenmeye başlar.";
			link.l1 = "Kan mı istiyorsunuz? Hayat fazla mı sıkıcı, heyecan mı yok? Alacaksınız kanınızı, siz hayvanlar!";
			link.l1.go = "francois_duel";
			link.l2 = "Ay canım, ne kadar da korktum! İşiniz bittiyse, beyler, gitmem gereken yerler var.";
			link.l2.go = "alonso_refuse";
		break;
		
		case "alonso_1":
			dialog.text = "It won't look good if our captain backs down from a public challenge. Just give that nobleman a good whack; we know you're great with a sword!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog9");
		break;
		
		case "alonso_refuse":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog6");
		break;
		
		case "francois_refuse":
			dialog.text = "Korkak! Serseri! Sıçan! Korktun mu, alçak? Hepiniz gördünüz mü bunu?! Richard, onu yine de öldüreceğim!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog4");
		break;
		
		case "francois_duel":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuelDialog");
		break;
		
		case "francois_sit":
			dialog.text = "S-serseri! Sorun değil, yaralanmalara alışığım. İyileşirim ve...";
			link.l1 = "Bu bir tehdit gibi geliyor, Albay. Ve tehditlere pek sıcak bakmam.";
			link.l1.go = "francois_sit_kill";
			link.l2 = "İyileştikten sonra, sakın subaylar arasında yaralanma hikayeni ballandıra ballandıra anlatmayı unutma.";
			link.l2.go = "francois_sit_taunt";
		break;
		
		case "francois_sit_kill":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_FinishFrancois");
		break;
		
		case "francois_sit_taunt":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			Notification_Approve(true, "Helena");
			AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 300);
			AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 300);
			
			AddDialogExitQuestFunction("HelenDrinking_SpareFrancois");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenSleep_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}
