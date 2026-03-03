// Алонсо де Мальдонадо
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bir şeye ihtiyacın var mı?";
			link.l1 = "Hayır, hiçbir şey.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "ksochitam":
			dialog.text = "Dur, Kaptan "+GetFullName(pchar)+"...";
			link.l1 = "İspanyol askerlerinin burada olmasına artık şaşırmıyorum bile... Sanırım peşimde birilerinin olmasına alıştım. Bu Allah'ın unuttuğu adada ne arıyorsun, Kastilyalı? Kolay yoldan keyif çatmanın peşinde misin?";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "Benim adım Alonso de Maldonado. Bu sana bir şey ifade etmeyebilir, ama Diego de Montoya adını duymuş olabilirsin. O benim en yakın arkadaşımdı. Hayatımı kurtardı, şimdi ise onun kanı senin ellerinde.";
			link.l1 = "Sanırım beni buraya kadar takip ettin, intikam almak için?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "Ben sadece intikam peşinde değilim. Bildiğim kadarıyla, Kukulcán'ın maskesi sende mi?";
			link.l1 = "Vay canına! Bir hazine avcısı daha! Don Diego'nun başlattığı ama yarım kalan iş için mi geldin?";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			dialog.text = "Hazinelerle ilgilenmiyorum. Tayasal'daki zenginlikleri gördüm. Miguel Dichoso oradan bir lokmadan fazlasını çıkaramadı. Benim istediğim maske.";
			link.l1 = "Tayasal'a mı gittin? Buna inanmak zor. Bildiğim kadarıyla, o keşif gezisinden sağ çıkan tek kişi Dichoso'ydu.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			dialog.text = "Ben Tayasal'a, Dichoso oraya varmadan yirmi yıl önce gittim. Aynı dönemde o deli büyücü Kanek, bu adada maskeyi saklamak için o iğrenç insan kurbanı ritüelini kullandı.";
			link.l1 = " Duyduklarıma inanamıyorum! Sen, Hakikat Muhafızı yaratıldığında oraya kurban edilmek için getirilen aynı fatihler grubunun bir parçası mıydın? Hepiniz ölmüşsünüz!";
			link.l1.go = "ksochitam_5";
		break;
		
		case "ksochitam_5":
			dialog.text = "Hepimiz değil. Ben kurtuldum.";
			link.l1 = "Itza neden seni bağışlamaya karar verdi? Seni diğerlerinden farklı kılan ne?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "Sen anlamazsın. Açıkçası, ben de anlamamıştım. Kimse bana acımadı. Sanki dün gibi hatırlıyorum... O vahşi, Casco'nun sırtından bir deri parçası kesip onu öldürdükten ve çılgınlar gibi ulumaya başladıktan hemen sonra, sanırım putun içine çekildim. Gözümü açtığımda Tayasal'dan çok uzakta, yirmi yıl sonra uyandım ama bana bir an gibi gelmişti!";
			link.l1 = "Bir uzay-zaman girdabı... Kahretsin, Ksatl Cha'nın söylediği her şey doğruymuş! Maskeyi nasıl buldun? Ona neden ihtiyacın var?";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			dialog.text = "Çılgın bir Hintli büyücünün çağırdığı cehennem yaratığını durdurmalıyım. Bu iğrenç varlık, dünyamızı bir ateş çemberine çevirmek istiyor!";
			link.l1 = "Hmm... Baba Vincento ile konuştun, değil mi? Engizitör hem tavşanla koşuyor hem de köpeklerle avlanıyor. Şaşırdım mı? Hiç de değil. Seni beni bulup düelloya çağırmak için mi gönderdi? Aferin! Görevini tamamladın, Don Alonso!";
			link.l1.go = "ksochitam_8";
		break;
		
		case "ksochitam_8":
			dialog.text = "Tanrı, kötülüğe karşı savaşta elimi güçlendiriyor. Tayasal'a döneceğim ve maskeyi kullanarak kapıları sonsuza dek mühürleyeceğim. Artık hiçbir insan kılığındaki iblis dünyamıza adım atamayacak.";
			link.l1 = "Planınızda ufak bir sorun var, Don Alonso. Şeytan ZATEN aramızda. Tek yapmamız gereken, onun bu kapılardan ÇIKMASINA izin vermemek. Maskeyi ondan uzak tuttuğunuz sürece bunu başaramaz. ";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "Bundan fazlası gerekecek. Hangimiz haklı olursak olalım, bir şey kesin: kapılar sonsuza dek kapatılmalı. Ve bunu yapmanın tek bir yolu var: Tayasal’daki sunaktaki maskeyi yok etmek. Bunu yaparsak, iblis tüm gücünden mahrum kalacak.";
			link.l1 = "Hm. En iyi şansımızın bu olduğuna katılıyorum... Tayasal'a nasıl gitmeyi düşünüyorsun? Oraya giden yolu biliyor musun?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "O zamanlar kullandığımız kolay yol artık yok. Yollar taşların altında kalmış, ormanlarda kaybolmuş. Şehre başka bir yol var, ama uzun ve tehlikeli. Yol, Yucatan'ın en kuzey koyundan başlıyor.\nPeder Vincento ve Don Ramon de Mendoza'nın yardımıyla seçkin askerlerden bir birlik toplayacağım ve Itza vahşileri tarafından korunan selva boyunca savaşarak ilerleyeceğiz. Kolay olmayacak, ama inancımız adına vereceğimiz bu mücadelede Tanrı bize güç ve cesaret verecek.";
			link.l1 = "Don Alonso, benim arzularım sizinkilerle örtüşüyor. Kinimizi bir kenara bırakıp güçlerimizi birleştirmenin zamanı gelmedi mi? Birlikte bu seferi başarıyla tamamlamak için daha fazla şansımız olur.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "Ben bir İspanyol askeriyim. Ne kafirlerle ittifak kurarım, ne de Fransızlarla anlaşma yaparım. Üstelik, Don Diego için sana zaten kin ilan ettim. Canı canla ödeyeceksin!";
			link.l1 = "İnatçısın da inatçısın, Don Alonso! Orada durmuşsun, dünyayı büyük bir kötülüğün tehdit ettiğini anlatıyorsun, ama yine de böylesine devasa bir işte sana yardım etmeme izin vermiyorsun!";
			link.l1.go = "ksochitam_12";
		break;
		
		case "ksochitam_12":
			dialog.text = "Artık kararları ben veriyorum, Peder Vincento değil! Duanı et ve ölmeye hazırlan, Fransız kaptan!..";
			link.l1 = "Ah, son birkaç ayda bunu o kadar çok duydum ki! Hazır ol, inatçı şövalye!";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_mushketer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_MaldonadoDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			if (MOD_SKILL_ENEMY_RATE > 4) Ksochitam_CreateMaldonadoHelpers();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
