void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold;
	string attrL, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{	case "First time":
			dialog.text = "Bir şey mi istiyorsun?";
			link.l1 = "Hayır, hiçbir şey.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> Шарль на носу корабля, Алонсо подходит с диалогом
		case "StartSailor":
			dialog.text = "Güzel bir manzara, değil mi?";
			link.l1 = "Bu lanetli deniz iki aydır beni öldürmeye çalışıyor. Henüz başaramadı.";
			link.l1.go = "StartSailor_1_fencing";
			link.l2 = "Kesinlikle öyle. Bazen okyanus, aslında ne kadar küçük olduğumuzu hatırlatır insana.";
			link.l2.go = "StartSailor_1_leadership";
			link.l3 = "Denizde sadece iki hal olduğunu öğrendim: can sıkıntısı ya da dehşet. Bu... başka bir şey.";
			link.l3.go = "StartSailor_1_fortune";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "StartSailor_1_fencing":
			dialog.text = "Ha! İlk kez denizde misiniz, monsieur? Hava böyle sakinken, herkes kaptan kesilir. Tadını çıkarın, ne kadar sürecekse artık.";
			link.l1 = ""+GetFullName(pchar)+". Soylu biriyim, bilmiş ol. Bana 'monsieur' deme.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_1_leadership":
			dialog.text = "Ha! İlk kez denizde misiniz, monsieur? Hava böyle sakinken, herkes kaptincilik oynar. Tadını çıkarın, uzun sürmez.";
			link.l1 = ""+GetFullName(pchar)+". Soylu biriyim, bilmiş ol. Bana 'monsieur' deme.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "StartSailor_1_fortune":
			dialog.text = "Ha! İlk kez denizde misiniz, monsieur? Böyle sakin olduğunda, herkes kaptıncılık oynayabilir. Tadını çıkarın, ne kadar sürecek belli olmaz.";
			link.l1 = ""+GetFullName(pchar)+" . Soylu biriyim, bilesin. Bana 'monsieur' deme.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		case "StartSailor_2":
			dialog.text = "Emredersiniz, efendim. O halde, ilk seferiniz, efendim "+pchar.lastname+"?";
			link.l1 = "Bu kadar belli mi? Evet, ilk kez. Ve ben daracık kamaralarda, küflü gemi yemekleriyle yaşamak için doğmadım.";
			link.l1.go = "StartSailor_3";
		break;
		
		case "StartSailor_3":
			dialog.text = "Gün gibi ortada, siz tam bir karacısınız, efendim.";
			link.l1 = "Ağzını topla! Bir onur sahibiyle karşı karşıya olsam, eldivenimi yere atar ve hesap sorardım. Ama senin gibi bir köylüye - kulaklarını kesmek yeterli olacak.";
			link.l1.go = "StartSailor_4";
		break;
		
		case "StartSailor_4":
			dialog.text = "Belki Paris'te öyle olur. Ama buralarda, böyle laflar adamı balıklara yem edebilir. O kılıcı sallamadan önce bir düşünün, efendim – ve kaptanın sizi silahlı gezdirdiğine pişman olmasını istemeyin. Son belâcıyı ambarın dibine, farelerin bile dokunmadığı küflü peksimetle pis suya gönderdiler. Ve biliyor musunuz? Zavallı adam limana vardığımızda bir de üstüne para ödemek zorunda kaldı.";
			link.l1 = "Ne bekliyordum ki... Neyse, bu yanlış anlamayı unutalım. Kendime sürekli hatırlatmam gerekiyor, bu teneke Louvre'un yanından bile geçmez.";
			link.l1.go = "StartSailor_5";
		break;
		
				case "StartSailor_5":
			dialog.text = "Ha? Louvre? O da neyin nesiymiş?";
			link.l1 = "Ha! Louvre seçilmişlerin sarayıdır. Balo, davet, entrika...";
			link.l1.go = "StartSailor_6";
		break;
		
		case "StartSailor_6":
			dialog.text = "Ah... demek genelev. Bizde onlardan bolca var. Seçilmişlere özel oldukları söylenemez - paranı öde, hepsi senin olur.";
			link.l1 = "Ha! Pek de yanılmadın, denizci.";
			link.l1.go = "StartSailor_7";
		break;
		
		case "StartSailor_7":
			dialog.text = "Bu arada, adım Alonso. Söylesenize, sizi dünyanın öbür ucuna ne getirdi, efendim? Atlantik'i sadece bir denizciyle tartışmak için geçtiğinizi sanmıyorum.";
			link.l1 = "Babam hasta ve Gascony'deki malikanemizden ayrılamıyor. Bana... ağabeyimi bulma görevi verildi. O buraya bir iş için gelmişti ve o zamandan beri ondan hiçbir haber alamadık.";
			link.l1.go = "StartSailor_8";
		break;
		
		case "StartSailor_8":
			dialog.text = "Neden denizin tüm zorluklarına kendin katlanmak yerine güvenilir birini göndermiyorsun?";
			link.l1 = "Aile her şeyden önce gelir. Kaderini ilk karşıma çıkan adama emanet edemem.";
			link.l1.go = "StartSailor_9_nobilityplus";
			link.l2 = "İsterdim – ama babam ille de benim gitmemi istiyor. Nedenini hiç bilmiyorum.";
			link.l2.go = "StartSailor_9_nobilityminus";
		break;
		
		case "StartSailor_9_nobilityplus":
			dialog.text = "Ve kardeşinizin adı nedir?";
			link.l1 = "Michel de Monper.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "StartSailor_9_nobilityminus":
			dialog.text = "Ve kardeşinizin adı nedir?";
			link.l1 = "Michel de Monper.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "StartSailor_10":
			dialog.text = "De Monper? Ve siz "+pchar.lastname+"? Nasıl yani?";
			link.l1 = "Bana öyle bakma. Ben meşru oğluyum. Sadece annemin soyadını aldım.";
			link.l1.go = "StartSailor_11";
		break;
		
		case "StartSailor_11":
			dialog.text = "Utanacak bir şey yok. Burada, Yeni Dünya’da herkesin bir hikâyesi var. Mesela ben...";
			link.l1 = "Hiçbir şeyden utanmıyorum! Sadece bana Martinique'i anlat. Büyük bir şehir mi? Toulouse gibi mi?";
			link.l1.go = "StartSailor_12";
		break;
		
		case "StartSailor_12":
			dialog.text = "Bir şehir mi? Ha! Martinik bir ada. Fransa'nın Karayipler'deki en büyük topraklarından biri. Burada yakıcı kahve yetiştirirler, cehennem gibi kükürt çıkarırlar ve dünyanın en güzel kadınları burada doğar. Bana sorarsan, harika bir karışım.";
			link.l1 = "Kahveyle ya da kükürtle ilgilenmiyorum. Ama dur... bir ada mı? Koca bir adada kardeşimi nasıl bulacağım ki?";
			link.l1.go = "StartSailor_13";
		break;
		
		case "StartSailor_13":
			dialog.text = "Endişelenme. Saint-Pierre küçük bir kasaba — elbette Louvre değil, ama orman da sayılmaz. Ama Le François... Allah korusun — düzgün bir adamın orada işi olmaz.";
			link.l1 = "Gerekirse haydutlara da giderim. Michel her zaman beni beladan kurtarırdı. Şimdi sıra bende.";
			link.l1.go = "StartSailor_14";
		break;
		
		case "StartSailor_14":
			dialog.text = "Fena değil... karada yaşayan biri için.";
			link.l1 = "Yine başladın. Bu lanet Martinique'e ne zaman varacağız?";
			link.l1.go = "StartSailor_15";
		break;
		
		case "StartSailor_15":
			dialog.text = "Beş gün.";
			link.l1 = "Beş mi?!";
			link.l1.go = "StartSailor_16";
		break;
		
		case "StartSailor_16":
			dialog.text = "En azından. Ve korsanlar ortaya çıkarsa — hiç ulaşamayabiliriz. Küçük Antiller tehlikeli sulardır, değerli yükümüz olmasa bile.";
			link.l1 = "Yolcular hariç!";
			link.l1.go = "StartSailor_17";
		break;
		
		case "StartSailor_17":
			dialog.text = "Ha-ha! Merak etme. En kötü ihtimalle, seni bizzat ben ambarın içine saklarım — hangi korsan bir Gascon soylusunu rom fıçıları arasında arar ki! Sonuçta aptal değiliz — canlı bir Gascon'u romla karıştırmak... Baruttan beter patlar vallahi, ha-ha!";
			link.l1 = "Ha! Neyse ki rom bir ay önce bitmişti!";
			link.l1.go = "StartSailor_18";
		break;
		
		case "StartSailor_18":
			dialog.text = "Şey... böyle şeyleri yüksek sesle söylemesen iyi olur. İnsanlar romun bitmesinin sebebinin sen olduğunu düşünebilir.";
			link.l1 = "Pekala Alonso, yapmayacağım. Zaten o pisliği içmezdim. Savaş öncesi beni ambarına tıkma fikrine gelince — o iş olmaz.";
			link.l1.go = "StartSailor_20";
		break;
		
		case "StartSailor_20":
			dialog.text = "Neden olmasın?";
			link.l1 = "Ben bir soyluyum, kılıcı iyi kullanırım ve ambarın köşesine saklanmıyorum.";
			link.l1.go = "StartSailor_21_fencing";
			link.l2 = "Gerekirse — gemiyi savunur, diğerleriyle birlikte savaşırım. Başka ne yapabilirim?";
			link.l2.go = "StartSailor_21_leadership";
			link.l3 = "Ne zaman savaşacağımı, ne zaman kaçacağımı kendim belirlerim. Bakalım nasıl olacak.";
			link.l3.go = "StartSailor_21_fortune";
			locCameraFromToPos(-14.85, 4.73, 5.82, true, -10.30, 4.52, 6.14);
		break;
		
		case "StartSailor_21_fencing":
			dialog.text = "Ha. Belki de sende bir şeyler var. Ama dikkat et — Karayipler burnu havada gelenleri fena hırpalar. Korsanların öncüsüyle ilk karşılaşmanda sağ çıkamazsın. Hatta, Saint-Pierre’in dışında bir serseri seni göz açıp kapayıncaya kadar bıçaklar.";
			link.l1 = "Beni hiç tanımıyorsun.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_21_leadership":
			dialog.text = "Ha. Belki de sende bir şeyler var. Ama dikkat et — Karayipler, burnu havada gelenleri lime lime etmeye bayılır. Korsanların öncüsüyle ilk karşılaşmanda sağ çıkamazsın. Hatta, Saint-Pierre dışında serseri bir çapulcu seni göz açıp kapayıncaya kadar doğrar.";
			link.l1 = "Beni hiç tanımıyorsun.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "StartSailor_21_fortune":
			dialog.text = "Ha. Belki de sende bir şeyler var. Ama dikkat et — Karayipler burnu havada gelenleri fena hırpalar. Korsanların öncüsüyle ilk karşılaşmanda sağ çıkamazsın. Hatta, Saint-Pierre’in dışında bir serseri seni göz açıp kapayıncaya kadar doğrar.";
			link.l1 = "Beni hiç tanımıyorsun.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		case "StartSailor_22":
			dialog.text = "Ama Yeni Dünya'yı ve insanlarını tanıyorum. Eğer muhasebe defterlerinin arkasında solup gitmeyi ya da valinin konağında hizmet etmeyi düşünmüyorsan — her şeyi en baştan öğrenmen gerekecek.";
			link.l1 = "İyi ki burada uzun süre kalmayı düşünmüyorum.";
			link.l1.go = "StartSailor_23";
		break;
		
		case "StartSailor_23":
			dialog.text = "Sen öyle sanıyorsun. Avrupa'ya yolcu götürmek bizde pek sık olmaz. Kimi yolda ölür — hummadan, ipten ya da kurşundan. Kimi de burada kalır — sonsuza dek. Zayıf aristokratların kaptan, acımasız haydutların saygın çiftçi olduğunu gördüm. Parlak subayların ise beş parasız serseriye dönüştüğünü.";
			link.l1 = "Cehennem kadar cazip, ama Fransa'ya döneceğim. Beni bekleyen insanlar var.";
			link.l1.go = "StartSailor_24";
		break;
		
		case "StartSailor_24":
			dialog.text = "Ah evet, doğru. Hasta bir baba mı?";
			link.l1 = "Şöyle diyelim... Paris'te olmamı hiç istemeyen bir beyefendinin eşiyle aramda bir şeyler var. Ama birkaç ay geçsin — tutkular diner.";
			link.l1.go = "StartSailor_25";
		break;
		
		case "StartSailor_25":
			dialog.text = "Ha-ha-ha! O zaman kesinlikle doğru yere geldin. Karayipler kıskanç kocalardan kaçanlar için tam bir cennet. Burada zaman su gibi akıp geçer. Biraz bekle — belki sonunda sen de denizci olursun!";
			link.l1 = "Büyük ihtimalle kaptan olurum. Sıradan bir denizci olmaya hiç yatkın değilim, korkarım. Ağır iş bana göre değil.";
			link.l1.go = "StartSailor_26";
		break;
		
		case "StartSailor_26":
			dialog.text = "Fransa’da insanlar doğuştan yönetir. Ama gemide — kaptan kraldır, yargıçtır, Tanrı’dır. O şapkayı hak etmek için ne sınavlardan geçtiğini kimse bilmez. Burada herkes hak ettiğini alır. Güvertede dediğimiz gibi — herkes layığını bulur.";
			link.l1 = "Saçmalık. Kaptanlardan söz açılmışken — seninkisiyle konuşmam gerek, özellikle de beni aradığına göre. Hoşça kal, Alonso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_StartKino_6");
		break;
		
		// <-- Шарль на носу корабля, матрос подходит с диалогом
		
		// --> С Алонсо можно в любой момент поговорить
		case "AlonsoWait":
			dialog.text = "Bir şey mi sormak istedin?";
			if (PCharDublonsTotal() >= 60 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Alonso"))
			{
				link.l1 = "Monsieur Pinchon'dan geliyorum.";
				link.l1.go = "AlonsoGold_2";
			}
			link.l2 = "Hiçbir şey.";
			link.l2.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_2":
			dialog.text = "Ha! O dört göz seni de bu işe bulaştırdı mı?";
			link.l1 = "Dört göz?";
			link.l1.go = "AlonsoGold_3";
		break;
		
		case "AlonsoGold_3":
			dialog.text = "Onun gözlüğünü gördün mü? Aynen öyle! Ama yanlış anlama — tayfa Monsieur Pinchon’a saygı duyar. Gemide iyi doktor her zaman kıymetlidir. Üstelik iyi bir veznedardır da.";
			link.l1 = "Onunla ne işin var?";
			link.l1.go = "AlonsoGold_4";
		break;
		
		case "AlonsoGold_4":
			dialog.text = "Uhh... Kusura bakmayın, ama bu bizim kendi işimiz. Merak etmeyin — gemi kurallarını çiğnemiyoruz.";
			link.l1 = "Sıradan yasalar ne olacak?";
			link.l1.go = "AlonsoGold_5";
		break;
		
		case "AlonsoGold_5":
			dialog.text = "Bizim için sıradan yasaların önemi yok. Peki, bana ne kadar borç çıkardılar?";
			if (PCharDublonsTotal() >= 40)
			{
				link.l1 = "40 doblon.";
				link.l1.go = "AlonsoGold_DatDeneg_3_gold40";
			}
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "50 doblon.";
				link.l2.go = "AlonsoGold_DatDeneg_3_gold50";
			}
			if (PCharDublonsTotal() >= 60)
			{
				link.l3 = "60 dublon.";
				link.l3.go = "AlonsoGold_DatDeneg_3_gold60";
			}
			// link.l4 = "Her şeyi bir kez daha kontrol etmem lazım. Sonra tekrar geleceğim.";
			// link.l4.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_DatDeneg_3_gold40":
			dialog.text = "Altın işte burada. Saint-Pierre, geliyorum! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(40);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold50":
			dialog.text = "Altın işte burada. Saint-Pierre, geliyorum! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold60":
			dialog.text = "Altın burada. Saint-Pierre, geliyorum! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(60);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoWait_2":
			DialogExit();
			NextDiag.CurrentNode = "AlonsoWait";
		break;
		
		// <-- С Алонсо можно в любой момент поговорить
		
		// --> капитан на корабле, который идёт из Европы
		case "Captain":
			dialog.text = "Ah, Charles. Pek aceleci sayılmazsın, değil mi? Bir gemi kaptanı seninle konuşmak istediğinde, derhal gelmen gerekir. Emirleri yerine getirmekte zorlanıyor musun?";
			link.l1 = "Emir almaya alışık değilim, Kaptan.";
			link.l1.go = "Captain_2_fencing";
			link.l2 = "Affedersiniz, Kaptan, geciktim.";
			link.l2.go = "Captain_2_leadership";
			link.l3 = "Geminin — senin kuralların olduğu açıkça belirtildi.";
			link.l3.go = "Captain_2_sailing";
			if (bBettaTestMode)
			{
				link.l9 = "BetaTest (eğitimi atla ve oyuna Martinique'te başla)";
				link.l9.go = "BetaTest_StartGame";
			}
			pchar.questTemp.SharlieTutorial_CaptainDialog = true;
		break;
		
		case "Captain_2_fencing":
			dialog.text = "Yetkim sorgulanamaz. Denizde yolcuların başına ne kadar sık felaket geldiğini bilmiyorsun. Seni sağ salim Saint-Pierre’e ulaştırmakla ilgilendiğim için çok şanslısın.";
			link.l1 = "Ne diyorsun?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "Captain_2_leadership":
			dialog.text = "Özür kabul edildi. Şu anın tadını çıkar. Böyle gün batımlarını sık sık bulamazsın.";
			link.l1 = "Ne diyorsun?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "Captain_2_sailing":
			dialog.text = "Bu yolculukta bir şeyler öğrenmiş olman güzel. Kaptanın sözü kanundur — ve bazen bu, gemiden uzakta, karada bile geçerlidir.";
			link.l1 = "Ne diyorsun?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		case "Captain_3":
			dialog.text = "Kaptan. Lütfen bana denizcilik protokolüne uygun şekilde hitap edin.";
			link.l1 = "Ne diyorsunuz, Kaptan?";
			link.l1.go = "Captain_4";
		break;
		
		case "Captain_4":
			dialog.text = "Sizi bilgilendirmek isterim ki yelkenleri indirdik ve şu an sürükleniyoruz. Ne yazık ki, Martinique’e varışınız birkaç gün gecikecek.";
			link.l1 = "Ama neden, Kaptan?";
			link.l1.go = "Captain_5";
		break;
		
		case "Captain_5":
			dialog.text = "Çünkü öyle karar verdim.";
			link.l1 = "Bu, dün karşılaştığımız ve şu... adı neydi... oraya giden tüccar konvoyuyla bir şekilde ilgili mi...";
			link.l1.go = "Captain_6";
		break;
		
		case "Captain_6":
			dialog.text = "Capsterville. Dinle, "+pchar.name+": ciddi bir konuşma yapmamız gerekiyor. Sizi kamarama yemeğe davet ediyorum. Zil birazdan çalacak — o zaman medeni insanlar gibi konuşmaya vaktimiz olacak, geminin son şişe şarabını bitirirken.";
			link.l1 = "Davetiniz için teşekkür ederim. Onur duyarım, Kaptan.";
			link.l1.go = "Captain_7";
		break;
		
		case "Captain_7":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "Hazır olduğunda bana haber ver. Hâlâ biraz vaktimiz var, gemide dolaşabilirsin — ama mürettebatımı işlerinden alıkoyma.";
				npchar.SharlieTutorial_question_0 = true;
				// теперь можно пострелять из пушки
				sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
				SetLocatorEvent(sld.id, "event3", "SharlieTutorial_cannon_1");
			}
			else dialog.text = "Başka sorunuz var mı?";
			link.l1 = "(Her şeyi toparla) Hazırım, Kaptan. Sizinle — Burgundy şarabı bile içerim!";
			link.l1.go = "Captain_8";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "O dürbünle neye bu kadar dikkatle bakıyorsun... Kaptan?";
				link.l2.go = "Captain_7_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Kaptan, Alonso adında biriyle konuşma fırsatım oldu. Gemideki görevi nedir?";
				link.l3.go = "Captain_7_question_2_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
			{
				link.l4 = "Kaptan, bana geminden bahset. Bir pinas, değil mi?";
				link.l4.go = "Captain_7_question_3_1";
			}
			link.l5 = "Bir dahaki sefere kadar, Kaptan.";
			link.l5.go = "Captain_7_exit";
		break;
		
		case "Captain_7_exit":
			DialogExit();
			NextDiag.CurrentNode = "Captain_7";
			if (!CheckAttribute(npchar, "SharlieTutorial_Zapis"))
			{
				npchar.SharlieTutorial_Zapis = true;
				AddQuestRecord("SharlieTutorial", "0.1");
			}
		break;
		
		case "Captain_7_question_1_1":
			dialog.text = "Özel bir şey yok, sadece ufku gözlüyorum. Sürüklenen bir gemi kolay avdır.";
			link.l1 = "Korsan mı arıyorsun?";
			link.l1.go = "Captain_7_question_1_2";
		break;
		
		case "Captain_7_question_1_2":
			dialog.text = "Ya da İspanyollar. Fransız bayrağı altında, korumasız yol alıyoruz ve Küçük Antiller tam bir kavşak — hem de Jacques Barbazon’un bölgesi.";
			link.l1 = "Kim o? Bir vali mi?";
			link.l1.go = "Captain_7_question_1_3";
		break;
		
		case "Captain_7_question_1_3":
			dialog.text = "Daha da kötüsü — korsan baronlarından biri. Bu cellat kuşları kendilerine bir tür örgüt kurup Kıyı Kardeşliği adını verdiler. Karayipleri altı bölgeye ayırıp her birine bir baron yerleştirdiler ki, birbirlerini parçalamasınlar.";
			link.l1 = "Neden yetkililer bu konuda bir şey yapmıyor?";
			link.l1.go = "Captain_7_question_1_4";
		break;
		
		case "Captain_7_question_1_4":
			dialog.text = "Safsın, "+pchar.name+". Korsanlık yalnızca yerel yetkililer, ganimetten pay almak karşılığında belirli limanlarda onlara tamir ve ikmal izni verdiği için var. Bunu kabul etmek hoşuma gitmiyor ama bu kara vebayla gerçekten mücadele eden tek taraf İspanyollar. Onlar olmasaydı, gemimizi pahalı toplarla donatmamız ve ayrıca bir koruma tutmamız gerekirdi.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_1 = true;
		break;
		
		case "Captain_7_question_2_1":
			dialog.text = "Kıdemli denizci. Onu pek tanımam, ama şunu söyleyebilirim: her insanın dolabında bir iskelet varsa, Alonso’nun bütün bir mezarlığı var.";
			link.l1 = "Onun güvenilir biri olmadığını mı düşünüyorsun?";
			link.l1.go = "Captain_7_question_2_2";
		break;
		
				case "Captain_7_question_2_2":
			dialog.text = "Hiç de değil. Mürettebat için bu kadar deneyimli adamlar bulmanın kolay olduğunu mu sanıyorsun? Bir grup meyhaneci ayyaşını mürettebata benzetmek için en az bir yıl ve mükemmel bir lostromo gerekir. Üstelik, Alonso aynı zamanda tayfanın sesi. Bir kaptan alt rütbelerle konuşmaya tenezzül etmez, ama sıradan denizcilerin de çıkarları olduğunu unutmak hem aptalca hem de ölümcül olur. Gerektiğinde onları Alonso temsil eder.";
			link.l1 = "Peki ya mürettebat memnun değilse ne olur?";
			link.l1.go = "Captain_7_question_2_3";
		break;
		
		case "Captain_7_question_2_3":
			dialog.text = "Beni asacaklar, seni ise sadece bıçaklayacaklar. Bu kadar solgun bakma. Mürettebat paralarını alıyor, doyuyor, içiyor ve yaraları sarılıyorsa — kaptanla tayfanın arasındaki anlaşma yerine gelmiş olur. Ben kimsenin hayatını riske atmam, keyfimden ceza vermem, ganimeti paylaşırım, bazen de onları içki ve karaya çıkma izniyle şımartırım. Böylece o hassas dengeyi koruruz — ve bu yüzden gemi her zaman varacağı yere varır.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_2 = true;
		break;
		
		case "Captain_7_question_3_1":
			dialog.text = "Bir yarama dokundun, "+pchar.name+"! Güzelliğimden saatlerce bahsedebilirim. Üçüncü sınıf, yirmi toplu, çok hızlı — ‘tüccar’ kısmına aldanma!";
			link.l1 = "Silahlar ve hız kısmını anladım. Ama ‘oran’? ‘Tüccar’?";
			link.l1.go = "Captain_7_question_3_2";
		break;
		
		case "Captain_7_question_3_2":
			dialog.text = "Rütbeler, topların sayısına göre yapılan kabaca bir sınıflandırmadır. Yedinci rütbe neredeyse bir kayık sayılırken, birinci rütbe adeta bir kale gibidir. Ama bunu Avrupa’da — hele deniz subaylarının yanında — sakın tekrarlama.";
			link.l1 = "Neden olmasın? Bu bir denizci şakası mı?";
			link.l1.go = "Captain_7_question_3_3";
		break;
		
		case "Captain_7_question_3_3":
			dialog.text = "Seni tam bir aptal yerine koyup alay edecekler. Gerçek şu ki, düzgün bir donanmada rütbe sistemi farklıdır ve sadece savaş gemileri için geçerlidir. Ama burada, Karayipler'de, işler her zamanki gibi kendi usulümüzce yürür.";
			link.l1 = "Peki, gemine neden ‘tüccar’ dedin, ne demek istedin?";
			link.l1.go = "Captain_7_question_3_4";
		break;
		
		case "Captain_7_question_3_4":
			dialog.text = "Yine belirsiz bir tanım. Savaş gemileri — daha dayanıklıdır ve daha iyi ateş eder. Akıncılar — çalar ve kaçar. Tüccarlar — bolca yük, mürettebat ya da top taşıyabilir, ama dengeyi iyi kurmazlarsa hızları gülünç olur. Çok amaçlı gemiler de var, ama onlar hakkında söylenecek fazla bir şey yok; sahiplerinin ihtiyaçlarına kolayca uyum sağlarlar.";
			link.l1 = "Heyecanlanıyorsunuz, Kaptan.";
			link.l1.go = "Captain_7_question_3_5";
		break;
		
		case "Captain_7_question_3_5":
			dialog.text = "Gemimi seviyorum, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_3 = true;
		break;
			
		case "Captain_8":
			if (IsEquipCharacterByItem(pchar, "hat3"))
			{
				dialog.text = "Pekâlâ, şanslısın — elimde sadece Burgundy kaldı... Bir dakika, "+pchar.name+". Eski şapkamı nereden buldun?!\nDur. Hey, yukarıda, direklerde! Orada neler oluyor?";
				ChangeCharacterComplexReputation(pchar, "nobility", -1);
			}
			else dialog.text = "Pekâlâ, şanslısın — elimde sadece Burgundy kaldı\nDur. Hey, yukarıda, direklerde! Orada neler oluyor?";
			link.l1 = "...";
			link.l1.go = "Captain_9";
		break;
		
		case "Captain_9":
			DialogExit();
			DelLandQuestMark(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga");
		break;
		
		case "BetaTest_StartGame":	// досрочный выход на сушу
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		
		// <-- капитан на корабле, который идёт из Европы
		
		// --> Диалог с охранником каюты
		case "OhrannikCabin":
			dialog.text = "Beni affedin, Mösyö de More, ama oraya girmenize izin verilmiyor.";
			link.l1 = "Kaptanın kamarasına daha önce de gitmiştim. Artık bunu hatırlıyor olmalısın.";
			link.l1.go = "OhrannikCabin_1";
			link.l2 = "Ne yazık ki, kurnaz planım başarısız oldu. Elveda, denizci.";
			link.l2.go = "exit";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 12) NextDiag.TempNode = "OhrannikCabin";
			else NextDiag.TempNode = "OhrannikCabin_again";
			if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikStay"))
			{
				LAi_SetStayType(npchar);
				npchar.SharlieTutorial_OhrannikStay = true;
				DeleteQuestCondition("SharlieTutorial_OhrannikStopaet");
			}
		break;
		
		case "OhrannikCabin_1":
			dialog.text = "Beni affedin, monsieur, ama koşullar değişti.";
			link.l1 = "Ve tam olarak ne oldu?";
			link.l1.go = "OhrannikCabin_2";
		break;
		
		case "OhrannikCabin_2":
			dialog.text = "Yolculuğun bitmesine az kaldı, kaptan da kimsenin değerli eşyalarını çalıp Le François gibi haydutların yuvasına kaçmasını istemez.";
			link.l1 = "Kaptanın böyle bir emir verirken beni düşündüğünden şüpheliyim.";
			link.l1.go = "OhrannikCabin_3";
		break;
		
		case "OhrannikCabin_3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 12)
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Pekâlâ... haklısınız. Ayrıca kaptanın kamarasında birden fazla kez yemek yediniz zaten. Devam edin, Mösyö de More.";
					link.l1 = "İşte böyle!";
					link.l1.go = "OhrannikCabin_4";
					Notification_Skill(true, 12, SKILL_LEADERSHIP);
				}
				else
				{
					dialog.text = "İm... ima ne? Öyle bir şey demek istemedim, monsieur de More!";
					link.l1 = "O halde beni geçirmelisin.";
					link.l1.go = "OhrannikCabin_3_1";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Monsieur, elbette kaptanın kamarası halka açık bir geçit değildir. Emirler emirdir.";
					link.l1 = "Kahretsin, bir an önce karaya çıkmak istiyorum. Bu gerçekten aşağılayıcı!";
					npchar.SharlieTutorial_OhrannikFail = true;
				}
				else
				{
					dialog.text = "Bayım, bunu zaten konuştuk. Sizi içeri alamam.";
					link.l1 = "Her zamanki gibi inatçısın, denizci. Elveda.";
				}
				link.l1.go = "exit";
				NextDiag.TempNode = "OhrannikCabin_again";
				Notification_Skill(false, 12, SKILL_LEADERSHIP);
			}
		break;
		
		case "OhrannikCabin_3_1":
			dialog.text = "Eh... peki. Sanırım bundan büyük bir zarar gelmez.";
			link.l1 = "İşte böyle!";
			link.l1.go = "OhrannikCabin_4";
			Notification_Skill(true, 12, SKILL_LEADERSHIP);
		break;
		
		case "OhrannikCabin_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			LocatorReloadEnterDisable("Quest_Ship_deck_Medium_trade", "reload_cabin", false);
		break;
		
		case "OhrannikCabin_again":
			dialog.text = "Başka bir şey, monsieur? Sizi içeri alamam — kaptan eşyaları konusunda endişeli.";
			link.l1 = "Hırsızlık mı ima ediyorsun, denizci? Dikkatli konuş. Bu düpedüz itham!";
			if (CheckAttribute(npchar, "SharlieTutorial_OhrannikFail")) link.l1.go = "OhrannikCabin_3";
			else link.l1.go = "OhrannikCabin_1";
			link.l2 = "Hiçbir şey, denizci.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OhrannikCabin_again";
		break;
		
		// <-- Диалог с охранником каюты
		
		// --> матрос ругается на ГГ, который активировал брашпиль
		case "SailorWithWindlass_1":
			dialog.text = "Hey, sen soylu budala! Ne yapıyorsun, şeytanı ırgatın içine mi tıkmaya çalışıyorsun?!\nKraliyet ayağınla tıpayı tekmeledin! Hepimizi dibe göndermeye mi niyetlisin?!\nBize bir iyilik yap — Fransız sümüğünden başka hiçbir şeye dokunma!";
			link.l1 = "Bu tam olarak nedir?";
			link.l1.go = "SailorWithWindlass_2";
		break;
		
		case "SailorWithWindlass_2":
			dialog.text = "Bu ırgat, seni sersem. Demiri yukarı çeker. Eğer sabitlenmemişse — gemiyi parçalara ayırır ya da birini fıçıdaki ringa balığı gibi sarar!";
			link.l1 = "Ha... Ve eğer diğer tarafa çevirirsen — demiri indiriyor, değil mi?";
			link.l1.go = "SailorWithWindlass_3";
		break;
		
		case "SailorWithWindlass_3":
			dialog.text = "Hayır, dahi, zamanı geri alıyor. Ama ne yazık ki sen zaten doğmuşsun!";
			link.l1 = "Pekâlâ, kimseye bir şey olmadı, değil mi? Gemiler gerçekten karmaşık makineler. Daha dikkatli olacağım.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_windlass_8");
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		// <-- матрос ругается на ГГ, который активировал брашпиль
		
		// --> матрос ругается на ГГ, который активировал пушку
		case "SailorWithCannon_1":
			dialog.text = "O topun uzun namlusuna, az önce gün batımına hayranlıkla baktığın gibi bakıyorsun.";
			link.l1 = "Beni izlemekten keyif alıyorsun, Alonso. Anlat bakalım, bu askeri mühendislik harikası hakkında ne biliyorsun?";
			link.l1.go = "SailorWithCannon_2";
		break;

		case "SailorWithCannon_2":
			dialog.text = "Bu on altı librelik bir toptur. Her savaş gemisinde bunlardan yoktur.";
			link.l1 = "Bununla bir şeye isabet ettirmek kolay mı?";
			link.l1.go = "SailorWithCannon_3";
		break;

		case "SailorWithCannon_3":
			dialog.text = "Boş namlu mesafesinde — her şeyi paramparça ederiz. Yüz yardda oyunun içindeyiz. Daha uzakta — çoğunlukla gürültü ve alev, ama hiç yoktan iyidir.";
			link.l1 = "Yüz metre — ve düşman da aynısını yapabilir.";
			link.l1.go = "SailorWithCannon_4";
		break;

		case "SailorWithCannon_4":
			dialog.text = "Doğru. Ama her şey mürettebatın uyumuna ve topçunun ustalığına bağlı. Ne yazık ki bizimki uyuyor — yoksa sana ders üstüne ders verir, sonra da seni topun içine tıkardı, ha!";
			link.l1 = "Topçu bir subay, değil mi?";
			link.l1.go = "SailorWithCannon_5";
		break;

		case "SailorWithCannon_5":
			dialog.text = "Genellikle öyle. En azından yarı yetenekli bir topçumuz yoksa, dövüşmekten kaçınmak en iyisi — topları denize atıp kaçmak daha mantıklı olur.\nTüccar kaptanlar nadiren altı libreliklerden büyük top taşır — ya korumalarına ya da şanslarına güvenirler.\nBu da mantıklı: ağır toplar ve cephane olmayınca, gemi daha iyi yol alır ve satacak daha çok yük taşır.\nKaptanımız bu güzelliklere servet harcamasaydı, belki elimizde biraz rom kalırdı. Of.";
			link.l1 = "Kaptan top ateşini bizzat yönetmez mi?";
			link.l1.go = "SailorWithCannon_6";
		break;

		case "SailorWithCannon_6":
			dialog.text = "İyi bir topçu ve mürettebat varsa, gerek bile kalmaz. Ama sana şunu söyleyeyim: Bir kaptan emir vermek yerine topları bizzat nişan alırsa — düşman gemileri delik deşik olur.";
			link.l1 = "Bir tane ateş edebilir miyim?";
			link.l1.go = "SailorWithCannon_7";
			link.l2 = "Teşekkür ederim bu ilginç ders için, Alonso. Denizcilik bilgeliğiyle dolu gerçek bir hazine sandığısın.";
			link.l2.go = "SailorWithCannon_7_exit";
		break;
		
		case "SailorWithCannon_7_exit":
			dialog.text = "Tabii! Ama yine de toplara dokunma ve tayfayı huzursuz etme.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_11");
		break;

		case "SailorWithCannon_7":
			dialog.text = "Ateş etmek mi? Pek sanmam. Bir atış yapmak için kaptanın izni gerekir. Hemen ona soracağım!";
			link.l1 = "Gerek yok!";
			link.l1.go = "SailorWithCannon_8";
		break;

		case "SailorWithCannon_8":
			dialog.text = "Kaa-ap'tan!";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieTutorial_cannon_3");
		break;
		
		case "CaptainWithCannon_1":
			dialog.text = "Ne oldu, Alonso?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_2";
		break;

		case "CaptainWithCannon_2":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_3":
			dialog.text = "Bay Charles, topu ateşlemeyi öneriyor — tamamen eğitim amaçlı.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_4";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;
		
		case "CaptainWithCannon_4":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_5", "Quest\Sharlie\Tutorial.c");
		break;
		
		case "CaptainWithCannon_5":
			dialog.text = "Mürettebatın çıkarlarını gözettiğini sanıyordum, Alonso. Ama bakıyorum ki, şimdi de nöbetçileri uyandırıp herkesi en kaba şekilde ayağa kaldırmayı öneriyorsun?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_6";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_6":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_7", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_7":
			dialog.text = "Bence onların kanını kaynatıp hazırlamak akıllıca olurdu. Açıkta sürükleniyor olmamız hoşuma gitmiyor. Bir şey olabilir.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_8";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;

		case "CaptainWithCannon_8":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_9", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_9":
			dialog.text = "Şeytanın kulağına kurşun!.. Peki. Bir yudum. Boş.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_10";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_10":
			dialog.text = "Keyfinize bakın, "+pchar.name+". Mürettebatı toplayacağız... senin hesabına, ha ha!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_5");
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), pchar);
		break;
		
		// <-- матрос ругается на ГГ, который активировал пушку
		
		// --> Диалог с матросом, который хочет рома
		case "SailorWantRum":
			dialog.text = "Bir dakikanızı ayırır mısınız, monsieur?";
			link.l1 = "Konuş, denizci.";
			link.l1.go = "SailorWantRum_1";
		break;

		case "SailorWantRum_1":
			dialog.text = "Sizinle tanışmak bir zevk, monsieur. Benim adım Henry. Biraz para kazanmak ister misiniz?";
			link.l1 = "Az dediğinde ne kadar az?";
			link.l1.go = "SailorWantRum_2";
		break;

		case "SailorWantRum_2":
			dialog.text = "Beş yüz peso.";
			link.l1 = "Ne kadar mı dedin?! O kadar para için ne yapmamı istiyorsun? İsyan mı başlatayım?";
			link.l1.go = "SailorWantRum_3";
		break;

		case "SailorWantRum_3":
			dialog.text = "Aman Tanrım, monsieur! Bağırmanıza gerek yok!";
			link.l1 = "Bu çok para, denizci. Paris'te bununla rahat bir hayat sürebilirdin.";
			link.l1.go = "SailorWantRum_4";
		break;

		case "SailorWantRum_4":
			dialog.text = "Ah, cehaletinden faydalanmayacağım. Burada Karayipler'de 500 peso hiçbir şey. Kaptanlar ve tüccarlar o kadar çok mal getiriyor ki, işe yarar bir şeyin fiyatı uçmuş durumda. Bazen nadir bir kılıç, küçük bir gemi kadar pahalıya mal oluyor.";
			link.l1 = "Bu delilik.";
			link.l1.go = "SailorWantRum_5";
		break;

		case "SailorWantRum_5":
			dialog.text = "Ne diyebilirim ki? Hepimiz işlerin yoluna girmesini ve fiyatların normale dönmesini bekliyoruz. Peki, 500 peso kazanmak ister misin?";
			link.l1 = "Önce, işin ne olduğunu bilmek istiyorum.";
			link.l1.go = "SailorWantRum_6";
		break;

		case "SailorWantRum_6":
			dialog.text = "Gemi­deki talihsiz rom durumu­nun farkında­sındır elbet. Ama eminim ki bir yerlerde hâlâ birkaç şişe kalmıştır. Şişedeki rom, fıçıdaki ucuz içkiden bambaşka. Tadı harika, zehirlenmeyi önler, koluna ve sağlığına güç verir — gerçek bir hazine. Özellikle de yolculuğun sonunda, ufuk gözünü döndürmeye başladığında.";
			link.l1 = "Peki, onunla ne yapacaksın? Neden kendin aramıyorsun?";
			link.l1.go = "SailorWantRum_7";
		break;

		case "SailorWantRum_7":
			dialog.text = "Ne zaman vaktim olacak ki? Adamımız az, üç kişilik iş yapıyorum. Ruma gelince, onu tekrar satacağım — bir alıcı bulurum.";
			link.l1 = "Doğruluğa değer veren bir adamı takdir ederim.";
			link.l1.go = "SailorWantRum_8";
		break;
		
		case "SailorWantRum_8":
			dialog.text = "Ee, işi kabul edecek misin? Üç şişeye ihtiyacım var.";
			link.l1 = "Deneyeceğim, ama söz veremem.";
			link.l1.go = "SailorWantRum_9";
			link.l2 = "Bu işi reddetmeyi tercih ederim. Böyle bir iş bana yakışmaz.";
			link.l2.go = "SailorWantRum_10";
		break;

		case "SailorWantRum_9":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRum");
		break;

		case "SailorWantRum_10":
			dialog.text = "Yazık, ama kin tutacak değilim. İyi akşamlar, efendim.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
			npchar.SailorWantRum_Done = true;
			DelLandQuestMark(npchar);
		break;

		case "SailorWantRum_PrinestiRum": // ждёт ром
			dialog.text = "Evet, monsieur "+pchar.lastname+"";
			if (GetCharacterItem(pchar, "potionrum") >= 3 && !CheckAttribute(npchar, "questTemp.SailorWantRum_Done"))
			{
				link.l1 = "İşte üç şişe romunuz.";
				link.l1.go = "SailorWantRum_PrinestiRum_2";
			}
			if (PCharDublonsTotal() >= 42 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Anri"))
			{
				link.l2 = "Henry, Monsieur Pinchon’dan sana bir şey getirdim.";
				link.l2.go = "RumGold_2";
			}
			link.l3 = "Hiçbir şey.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "RumGold_2":
			dialog.text = "Ona her zaman yardımcı olmaktan mutluluk duyarım! Bu sefer bana ne kadar borçlu?";
			if (PCharDublonsTotal() >= 28)
			{
				link.l1 = "28 doblon.";
				link.l1.go = "RumGold_DatDeneg_gold28";
			}
			if (PCharDublonsTotal() >= 35)
			{
				link.l2 = "35 doblon.";
				link.l2.go = "RumGold_DatDeneg_gold35";
			}
			if (PCharDublonsTotal() >= 42)
			{
				link.l3 = "42 doblon.";
				link.l3.go = "RumGold_DatDeneg_gold42";
			}
			// link.l4 = "Her şeyi bir kez daha kontrol etmem lazım. Hemen döneceğim.";
			// link.l4.go = "RumGold_DatDeneg_3";
		break;

		case "RumGold_DatDeneg_gold28":
			dialog.text = "Teşekkür ederim, monsieur "+pchar.lastname+"   Haznedara selamlarımı ilet. ";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(28);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold35":
			dialog.text = "Teşekkür ederim, monsieur "+pchar.lastname+"   Haznedara selamlarımı ilet. ";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(35);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold42":
			dialog.text = "Teşekkür ederim, monsieur "+pchar.lastname+"  Haznedara selamlarımı ilet. ";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(42);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "SailorWantRum_PrinestiRum_2":
			dialog.text = "Teşekkür ederim, monsieur "+pchar.lastname+". Bu gerçekten ustaca bir işti!";
			link.l1 = "Umarım paramı da aynı kolaylıkla alırım.";
			link.l1.go = "SailorWantRum_PrinestiRum_3";
			RemoveItems(pchar, "potionrum", 3);
			npchar.SailorWantRum_Done = true;
		break;

		case "SailorWantRum_PrinestiRum_3":
			dialog.text = " Parayla olmayan bir ödeme düşünür müydünüz? ";
			link.l1 = "Göründüğün kadar dürüst değilsin, anlaşılan.";
			link.l1.go = "SailorWantRum_PrinestiRum_4";
		break;

		case "SailorWantRum_PrinestiRum_4":
			dialog.text = "Hayır, hayır! Para istiyorsan, para alırsın! Ama biraz bilgi de paylaşabilirim.";
			link.l1 = "Ne tür bir bilgi?";
			link.l1.go = "SailorWantRum_PrinestiRum_5";
		break;

		case "SailorWantRum_PrinestiRum_5":
			dialog.text = "Sana denizcilik hakkında kitaplarında bulamayacağın çok şey anlatabilirim.";
			link.l1 = "Pekâlâ, o zaman bana hayatımın en pahalı dersini ver.";
			link.l1.go = "SailorWantRum_PrinestiRum_6";
			link.l2 = "Beş yüz bahşiş, beş yüz altının yerini tutmaz. Parayı alıyorum.";
			link.l2.go = "SailorWantRum_PrinestiRum_money";
		break;

		case "SailorWantRum_PrinestiRum_money":
			dialog.text = "Buyurun, monsieur "+pchar.lastname+". Ve tekrar teşekkür ederim!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
			AddMoneyToCharacter(pchar, 500);
		break;
		
		case "SailorWantRum_PrinestiRum_6":
			dialog.text = "Gerçekten öyle olmasını umuyorum, monsieur "+pchar.name+", dersimin faydalı olacağını umarım. Seyir nedir biliyor musun?";
			link.l1 = "Şaşırırsın ama biliyorum. Hatta okuyabiliyorum bile. Seyircilik, mesela bir gemi için, uzaydaki konumunu belirleyip rota çizmektir.";
			link.l1.go = "SailorWantRum_PrinestiRum_7";
		break;

		case "SailorWantRum_PrinestiRum_7":
			dialog.text = "Ah. Yıldızlar ve haritalardan mı bahsediyorsun? Hayır, o işlerden anlamam. Onlar dümencinin ya da kaptanın işi. Buralarda seyircilik, gemiyi idare edip komuta edebilmek demektir.";
			link.l1 = "Burada kim var?";
			link.l1.go = "SailorWantRum_PrinestiRum_8";
		break;

		case "SailorWantRum_PrinestiRum_8":
			dialog.text = "Karayipler’de böyle işler, nedenini bana sorma. Yani, seyir bilgin ne kadar iyiyse, gemiden o kadar fazla hız ve çeviklik çıkarabilirsin. Mürettebatın da yelkenleri daha hızlı idare eder. Ama en önemli şey bu değil.";
			link.l1 = "Gerilimi nasıl tırmandıracağını iyi biliyorsun.";
			link.l1.go = "SailorWantRum_PrinestiRum_9";
		break;

		case "SailorWantRum_PrinestiRum_9":
			dialog.text = "Seyir bilginiz ne kadar iyiyse, o kadar büyük bir gemiye komuta edebilirsiniz! Eğer seviyenizden daha gelişmiş bir gemi alırsanız, dikkatiniz, enerjiniz ve hatta sağlığınızdan olabilirsiniz!";
			link.l1 = "Kulağa tehlikeli geliyor. Bunca zaman bunu bilmeden hayatta kalmam tuhaf.";
			link.l1.go = "SailorWantRum_PrinestiRum_10";
		break;

		case "SailorWantRum_PrinestiRum_10":
			dialog.text = "Neyse ki, her şeyin uzmanı olman gerekmiyor. Eksiklerini kapatmak için her zaman iyi bir rotacı tutabilirsin. Yeter ki maaşını öde ve sana sadık kalsın. Yeteneklerini aşan bir gemide rotacını kaybetmek — hiç de hoş olmaz.";
			link.l1 = "Ders için sağ ol, Henry. İşime yarar mı emin değilim ama sanırım bilgi hiçbir zaman fazla olmaz.";
			link.l1.go = "SailorWantRum_PrinestiRum_11";
			AddCharacterSkillPoints(pchar, "Sailing", 3);
		break;

		case "SailorWantRum_PrinestiRum_11":
			dialog.text = "Rica ederim, monsieur "+pchar.lastname+". Ve tekrar teşekkür ederim!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;
		
		// <-- Диалог с матросом, который хочет рома
		
		// --> Диалог со старым матросом в трюме
		case "OldSailor":
			dialog.text = "(şarkı söylüyor) C’est la mère Michel qui a perdu son chat... Qui crie par la fenêtre à qui le lui rendra...";
			link.l1 = "Burada ne yapıyorsun, denizci?";
			link.l1.go = "OldSailor_1";
			NextDiag.TempNode = "OldSailor";
		break;
		
		case "OldSailor_1":
			dialog.text = "Şimdi ben de Madame Michel gibi oldum — kediyi arıyorum. Sadece ben bağırmıyorum — o bağırılmasından hoşlanmaz.";
			link.l1 = "Onu bu sabah gördüm — yine çizmelerime yapışmıştı.";
			link.l1.go = "OldSailor_2";
		break;

		case "OldSailor_2":
			dialog.text = "Bu bir şey değil. Kaptanın çizmeleri daha beterdi. Kedileri sever misin?";
			link.l1 = "Elbette biliyorum.";
			link.l1.go = "OldSailor_3";
			link.l2 = "Pek sayılmaz.";
			link.l2.go = "OldSailor_4";
		break;

		case "OldSailor_3":
			dialog.text = "Mantıklı. Yoksa o lanet olası farelerle nasıl başa çıkardık?";
			link.l1 = "Ama kedilere sonsuza kadar güvenemezsin, değil mi? Oldukça inatçı yaratıklardır.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "OldSailor_4":
			dialog.text = "Yazık. Kediler gemide çok sevilir ve değer görür. Yoksa o lanet farelerle nasıl başa çıkardık?";
			link.l1 = "Ama kedilere sonsuza kadar güvenemezsin, değil mi? Oldukça inatçı hayvanlardır.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "OldSailor_5":
			dialog.text = "Doğru. O yüzden arsenik kullanıyoruz. Ama Karayipler'de onu bulmak kolay mı, hadi bul da gör. Sonuçta yükümüzden oluyoruz — fareler romu bozuyor, peksimeti mahvediyor, geriye kalan her şeyi de kemiriyorlar.\nVe bizim kambiyecimiz diyor ki: 'Rahat olun, bu ticaret vergisi gibi bir şey.'\nAma biz gerçeği biliyoruz: adam tam anlamıyla tembel. Sevgili Chantal olmasa, kaptan onu çoktan ambarın dibine tıkıp fare avlatırdı, ha-ha!";
			link.l1 = "Kediyle iyi şanslar. Gitmem gerek.";
			link.l1.go = "OldSailor_6";
		break;

		case "OldSailor_6":
			dialog.text = "Bir dakika, monsieur. Sıradan bir denizci genellikle asil yolcuları sadece güvertede görür, ama siz buradasınız — ta ambarın dibine kadar inmişsiniz!";
			link.l1 = "Merak kediyi öldürür, ha-ha!";
			link.l1.go = "OldSailor_7";
		break;

		case "OldSailor_7":
			dialog.text = "Denizcilikle ilgileniyorsun demek, öyle mi?";
			link.l1 = "Görünüşe bakılırsa, her tayfa üyesi karaya varmadan önce beni gerçek bir denizci yapmaya kararlı.";
			link.l1.go = "OldSailor_8";
		break;

		case "OldSailor_8":
			dialog.text = "Şaşırtıcı değil. Deniz çoğumuza sadece keder getirmiş olsa da, işimizi seviyoruz. Ve bir denizci, biri gerçekten ilgi gösterdiğinde her zaman memnun olur.";
			link.l1 = "...";
			link.l1.go = "OldSailor_9";
		break;
		
		case "OldSailor_9":
			dialog.text = "Şimdi söyle bana: Bir kaptan için en önemli beceri nedir?";
			if (GetSummonSkillFromName(pchar, SKILL_SAILING) >= 6)
			{
				link.l1 = "Seyir. Komuta edebileceği geminin büyüklüğünü belirler.";
				link.l1.go = "OldSailor_10";
				Notification_Skill(true, 6, SKILL_SAILING);
			}
			else
			{
				link.l1 = "Yalan söylemeyeceğim — bilmiyorum.";
				link.l1.go = "OldSailor_9_1";
				Notification_Skill(false, 6, SKILL_SAILING);
			}
		break;

		case "OldSailor_9_1":
			dialog.text = "Üzülmeyin, monsieur. Mürettebatla konuşun, gemiyi keşfedin. Cevabı bulursanız — sizinle gerçekten büyüleyici bir şey paylaşacağım. Sanki bizden biriymişsiniz gibi.";
			link.l1 = "Bunu aklımda tutacağım. Hoşça kal!";
			link.l1.go = "exit";
			NextDiag.TempNode = "OldSailor_again";
		break;

		case "OldSailor_10":
			dialog.text = "Doğru! Şimdi daha zoru geliyor: kare yelkenler mi yoksa baş-kıç yelkenler mi — hangisi daha iyidir?";
			link.l1 = "Söylemesi zor, ama bir hile olduğunu hissediyorum. Her birinin kendine göre avantajları var, derim.";
			link.l1.go = "OldSailor_11";
		break;

		case "OldSailor_11":
			dialog.text = "Yine doğru! Eğer rüzgar arkandan esiyorsa kare yelkenler harikadır. Ama bir baştan kıça arma, rüzgarı çaprazdan bile yakalayabilir ve manevra yapabilir. Zamanını boşa harcamadığını görmek güzel, monsieur.";
			link.l1 = "Bu bilgilerin bir gün işime yarayacağından pek emin değilim... Tabii, gerçek bir denizci gibi davranıp sosyete hanımlarını etkilemek istersem, ha-ha!";
			link.l1.go = "OldSailor_12";
		break;
		
		case "OldSailor_12":
			dialog.text = "Ah, emin değilim, monsieur "+pchar.name+". Soylu olabilirsin — ama bize düzgün davranıyorsun. Bunu takdir ediyoruz. Kaptan bir şeyler çeviriyor. Yolunu bir kara kedi kesti.";
			link.l1 = "Saçmalık. Ne anlatıyorsun sen, denizci?";
			link.l1.go = "OldSailor_13";
		break;

		case "OldSailor_13":
			dialog.text = "Duyduğuma göre, birkaç gün önce Capsterville’e bir mektup göndermiş geçen bir gemiyle\nVe yolculuğun sonunda, herkes karayı görmeyi beklerken, kaybolmuş.";
			link.l1 = "Söylentiler umurumda değil. Neden uğraşayım ki? Ona kendim sorabilirim. Bir asilzade olarak bana doğruyu söylemekten kaçınmaz.";
			link.l1.go = "OldSailor_14";
		break;

		case "OldSailor_14":
			dialog.text = "Onu tanımıyorsunuz, monsieur "+pchar.name+". O yapardı — hem de nasıl. Ve şimdi öfkeli — anahtarını kaybetti.";
			link.l1 = "Anahtar?";
			link.l1.go = "OldSailor_15";
		break;

		case "OldSailor_15":
			dialog.text = "Kamarada, sandığının içinde. Sanırım bir yerlerde duruyordur.";
			link.l1 = "Anahtarı bulmak? Ben mi?";
			link.l1.go = "OldSailor_16";
		break;

		case "OldSailor_16":
			dialog.text = "Bu sana kalmış\nBu arada, monsieur "+pchar.name+" , biraz rom kaldı mı? Yoksa hepsini Henry'ye mi verdin, ha ha!";
			if (GetCharacterItem(pchar, "potionrum") >= 1)
			{
				link.l1 = "Evet, buyurun.";
				link.l1.go = "OldSailor_17";
			}
			link.l2 = "Korkarım hayır. O üç şişeyi bulmam bile mucizeydi.";
			link.l2.go = "OldSailor_16_1";
		break;

		case "OldSailor_16_1":
			dialog.text = "Doğru söylüyorsunuz. Size bol şans, monsieur "+pchar.name+". O çizgili alçağı aramaya devam edeceğim.";
			link.l1 = "Sana da bol şans, denizci.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\\Animals\\Cat_01.wav");
		break;
		
		case "OldSailor_17":
			dialog.text = "Mürettebata iyilik ettiniz, monsieur "+pchar.name+". İşte sana biraz şans getirecek bir tılsım!";
			link.l1 = "Delikli bir taş mı? Ne hoş.";
			link.l1.go = "OldSailor_18";
			GiveItem2Character(PChar, "talisman11");
			TakeItemFromCharacter(pchar, "potionrum");
		break;

		case "OldSailor_18":
			dialog.text = "Ne kadar istersen gül. Denizde tılsımların zararı olmaz.";
			link.l1 = "Siz denizciler çok batıl inançlısınız. Size bol şans dilerim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\\Animals\\Cat_01.wav");
		break;

		case "OldSailor_again":
			dialog.text = "Cevabı çoktan buldun mu? Bir kaptan için en önemli beceri nedir?";
			if (GetSummonSkillFromName(pchar, SKILL_SAILING) >= 6)
			{
				link.l1 = "Seyir. Komuta edebileceği geminin büyüklüğünü belirler.";
				link.l1.go = "OldSailor_10";
				Notification_Skill(true, 6, SKILL_SAILING);
			}
			else
			{
				link.l1 = "Henüz değil.";
				link.l1.go = "exit";
				NextDiag.TempNode = "OldSailor_again";
				Notification_Skill(false, 6, SKILL_SAILING);
			}
		break;
		
		// <-- Диалог со старым матросом в трюме
		
		// --> Диалог с матросом, которому нужен ящик с ядрами (Поль)
		case "SailorNeedBox":
			dialog.text = "Selam, delikanlı!";
			link.l1 = "Babam gibi görünmüyorsun. Şükürler olsun ki öyle.";
			link.l1.go = "SailorNeedBox_1";
		break;

		case "SailorNeedBox_1":
			dialog.text = "Ha! Böyle uzun boylu, asil bir oğlum olsa gurur duyardım. Ama ben ancak kendim gibi sıradan insanlara baba olabilirim.";
			link.l1 = "Pekâlâ, iltifatı kabul ediyorum. Sorun ne?";
			link.l1.go = "SailorNeedBox_2";
		break;

		case "SailorNeedBox_2":
			dialog.text = "Yardıma ihtiyacım var, delikanlı. Topların yanına cephane yığmam emredildi — bu tehlikeli sularda başımız derde girerse diye. Vardiyanın yarısını bu demir meretleri ambarlardan taşımakla geçirdim, son sandıkta belim iflas etti.";
			link.l1 = "Neden arkadaşlarına sormuyorsun? Denizciler birbirine yardım eder sanırdım.";
			link.l1.go = "SailorNeedBox_3";
		break;

		case "SailorNeedBox_3":
			dialog.text = "Kardeşliğimizin kesinlikle nefret ettiği bir şey varsa, o da iyi bir sebep olmadan ağır yük taşımaktır. Bugün kura bana çıktı — ambarlardan cephane sandıklarını sürüklüyorum. Berbat bir iş, benim kalitemde bir denizciye yakışmaz. Ama ne yapabilirsin ki?";
			link.l1 = "Sızlanmayı bırak. Yardım edeceğim. En azından herkesin beni korkuttuğu şu hücreyi bir göreyim.";
			link.l1.go = "SailorNeedBox_4";
			if (IsCharacterPerkOn(pchar, "HT3"))
			{
				link.l2 = "(Atlet) Kemerimdeki bu geniş kılıcı görüyor musun? Senden daha ağır. Topunu getiririm — hiç sorun değil.";
				link.l2.go = "SailorNeedBox_4";
			}
			link.l3 = "Ben el emeğiyle uğraşmam, denizci. Kasalarını kendin taşı.";
			link.l3.go = "SailorNeedBox_Net";
		break;

		case "SailorNeedBox_4":
			dialog.text = "Sağ ol, delikanlı. Sırtını incitmemeye bak!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBalls");
		break;
		
		case "SailorNeedBox_Net":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "SailorNeedBox_PrinestiBalls":	// ожидание выстрела
			dialog.text = "Nasıl gidiyor, delikanlı?";
			if (CheckCharacterItem(PChar, "BoxOfBalls"))
			{
				link.l1 = "İşte içkin. Daha büyük olurlar sanmıştım.";
				link.l1.go = "SailorWantRum_PrinestiBalls_2";
			}
			if (PCharDublonsTotal() >= 30 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Poli"))
			{
				link.l2 = "Adın Paul, değil mi?";
				link.l2.go = "BallsGold_2";
			}
			link.l3 = "Elveda.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "BallsGold_2":
			dialog.text = "Şey... e-evet.";
			link.l1 = "Adınız, Bay Pinchon'un bana verdiği listede var.";
			link.l1.go = "BallsGold_3";
		break;
		
		case "BallsGold_3":
			dialog.text = "Vay, bir an için... Evet, Paul - o benim, doğru. Ne kadar getirdin bana?";
			if (PCharDublonsTotal() >= 20)
			{
				link.l1 = "20 doblon.";
				link.l1.go = "BallsGold_DatDeneg_gold20";
			}
			if (PCharDublonsTotal() >= 25)
			{
				link.l2 = "25 dublon.";
				link.l2.go = "BallsGold_DatDeneg_gold25";
			}
			if (PCharDublonsTotal() >= 30)
			{
				link.l3 = "30 doblon.";
				link.l3.go = "BallsGold_DatDeneg_gold30";
			}
			// link.l4 = "Her şeyi bir kez daha kontrol etmem lazım. Sonra geri döneceğim.";
			// link.l4.go = "BallsGold_DatDeneg_3";
		break;
		
		case "BallsGold_DatDeneg_gold20":
			dialog.text = "Sağ ol, delikanlı.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(20);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold25":
			dialog.text = "Teşekkür ederim, delikanlı.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(25);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold30":
			dialog.text = "Sağ ol, delikanlı.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(30);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "SailorWantRum_PrinestiBalls_2":
			dialog.text = "Daha büyük olursa, düşmana hediye olur! Gövdeye isabet ederse — belki sadece birini yaralar. Ama kıça çarparsa, güverte boyunca top gibi sekip durur!";
			link.l1 = "Daha önce böyle bir şey gördün mü?";
			link.l1.go = "SailorWantRum_PrinestiBalls_3";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
		break;
		
		case "SailorWantRum_PrinestiBalls_3":
			dialog.text = "Kendi gözlerimle gördüm, delikanlı. İnsan öldürme makineleri icat etmede gerçekten usta. Mesela saçma mermisi — menzili kısa, gövdeyi delemez ama bir düzine adamı öteki dünyaya gönderebilir. Ya da zincirli gülle — yelkenlere isabet ederse onları paramparça eder! Bombalara gelince — hiçbir şey demem, hiç görmedim, Allah’a şükür! Şeytanın icadı onlar, hem de çok pahalı.";
			link.l1 = "Top güllelerinin ne kadar ölümcül olduğunu zaten gördüm — zavallı beline sor istersen.";
			link.l1.go = "SailorWantRum_PrinestiBalls_4";
		break;

		case "SailorWantRum_PrinestiBalls_4":
			dialog.text = "Eh, bana gerçekten büyük bir iyilik yaptın. Ben de sana borcumu ödeyeceğim. Al — neredeyse dolu birinci sınıf rom şişesi, ha-ha!";
			link.l1 = "Bunu nereden buldun? Herkes romun çoktan tükendiğini söylüyor. Böyle bir malzeme ile, birini sadece bir sandığı değil, ambarın tamamını taşımaya bile ikna edebilirdin.";
			link.l1.go = "SailorWantRum_PrinestiBalls_5";
			GiveItem2Character(PChar, "potionrum");
		break;

		case "SailorWantRum_PrinestiBalls_5":
			dialog.text = "Öyle oldu işte, delikanlı. Teşekkür ederim ve hoşça kal.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBallsFinal");
		break;
		
		// <-- Диалог с матросом, которому нужен ящик с ядрами
		
		// --> Диалог с офицером-торговцем, который торгует всяким
		case "OfficerTorgovets":
			dialog.text = "Ah, monsieur "+pchar.lastname+". Eğer uyumayı düşünüyorsan — şansın yok. Topçumuz senin yatağına el koydu. Bildiğin gibi, onu uyandırmak pek kolay değil.";
			link.l1 = "Şunu söylemeliyim ki, gerektiğinde — her şeyi gayet iyi duyar!";
			link.l1.go = "OfficerTorgovets_1";
			/*link.l2 = "Hayır.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets";*/
		break;
		
		case "OfficerTorgovets_1":
			dialog.text = "Bu hiçbir şey. Duyduğuma göre Sharp’ın tayfasında bir ara kör bir topçu varmış. Topların sesine göre nişan alırmış, diyorlardı.";
			link.l1 = "Bugün pek bir konuşkansınız, bay lostrom.";
			link.l1.go = "OfficerTorgovets_2";
		break;

		case "OfficerTorgovets_2":
			dialog.text = "Bunun bir sebebi var! Yakında karaya çıkıyoruz — elde kalan malları cingöz pesolara çevirmeye vakit geldi. Saint-Pierre'deki genelevler onları her zaman memnuniyetle karşılar, ha-ha!";
			link.l1 = "Garip, bu tür ufak tefek ticaret işleriyle gemide ilgilenenin sen olman, kambiyeci değil.";
			link.l1.go = "OfficerTorgovets_3";
		break;

		case "OfficerTorgovets_3":
			dialog.text = "Katip insanlarla konuşamaz ki! O iş için lostromolar var — hem lafı hem işi iyi bilirler, ha-ha! Katibin de elbette kendi hesabı vardır — ama ben o karanlık sulara dalmam.";
			link.l1 = "Bugün neler var?";
			link.l1.go = "OfficerTorgovets_4";
		break;

		case "OfficerTorgovets_4":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "Gemideki son şişe rom, birkaç uğurlu tılsım... ve işte! Eksiksiz bir hazine haritası.";
				link.l1 = "Tüccar olmalıydın, lostromos değil! Bakalım neler yapacaksın.";
				npchar.SharlieTutorial_question_0 = true;
			}
			else
			{
				dialog.text = "Başka bir şey?";
				link.l1 = "Bakalım neler yapabileceksin.";
			}
			link.l1.go = "OfficerTorgovets_5";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "Tılsımlar mı? Boynunda asılı olan gibi mi?";
				link.l2.go = "OfficerTorgovets_6_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Affedersiniz... bir hazine haritası mı dediniz?";
				link.l3.go = "OfficerTorgovets_6_question_2_1";
			}
			link.l4 = "Belki başka bir zaman.";
			link.l4.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets_4";
		break;
		
		case "OfficerTorgovets_5":
			DialogExit();
			NextDiag.CurrentNode = "OfficerTorgovets_4";
			sld = ItemsFromID("map_full");
			sld.price = 4000;
			LaunchItemsTrade(NPChar, 0);
		break;

		case "OfficerTorgovets_6_question_1_1":
			dialog.text = "Ah, keskin gözler, monsieur. Evet, 'Mercan Başlığı' — güzel bir şey. Özellikle de benim için. Eğer bir çıkarma ekibine liderlik etmem gerekirse — adamları toparlamama yardımcı oluyor.";
			link.l1 = "Gerçekten buna inanıyor musun?";
			link.l1.go = "OfficerTorgovets_6_question_1_2";
		break;

		case "OfficerTorgovets_6_question_1_2":
			dialog.text = "İnanmak zorunda değilim. Karayipler böyle işler, denizcinin kaderi de budur. Tılsımlar işe yarar şeylerdir. Eğer bizimle kalacaksan, yanında birkaç tane bulundurmanı tavsiye ederim — farklı durumlar için.";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "OfficerTorgovets_6_question_2_1":
			dialog.text = "Ah evet. Karayipler'de bu pek nadir değildir. Bazıları şanslı çıkar — köşeyi döner. Sonra ya vergilerini öder, sessiz ve uzun bir ömür sürerler... ya da altınlarını bir mağaraya saklarlar. Geriye kalan ise bir mezar, hazine... ve bir parça kağıt olur.";
			link.l1 = "Bu kadar mı yani?";
			link.l1.go = "OfficerTorgovets_6_question_2_2";
		break;

		case "OfficerTorgovets_6_question_2_2":
			dialog.text = "Tam olarak değil. Haritalar pahalıdır ve senin gibi başka avcıları da çeker. Üstelik bazen ganimet, yaşanan sıkıntıya bile değmez. Büyük Albert Blackwood bile başlarda zorlanmıştı. Hazine avcılığını mesleğin yaparsan — ne kadar çok bulursan, ödülün de o kadar büyük olur. Bir de şans getiren bir tılsımın varsa — daha da iyi!";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_2 = true;
		break;
		// <-- Диалог с офицером-торговцем, который торгует всяким
		
		// --> Диалог с офицером-казначеем
		case "OfficerKaznachey":
			dialog.text = "Monsieur "+pchar.lastname+"! Bir dakika.";
			link.l1 = "Yine mi nasihatlar, Mösyö Pinchon? Kıymetli mürekkebine dokunmadım!";
			link.l1.go = "OfficerKaznachey_2";
		break;

		case "OfficerKaznachey_2":
			dialog.text = "O zaman o küçük defterine neyle karalıyorsun? Kutsal suyla mı? Yolcu envanterinde mürekkep yoktu. Neyse, şu an daha büyük dertlerin var.";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_3";
		break;

		case "OfficerKaznachey_3":
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) sStr = "And two hundred more — for the broken windlass. The anchor cable snapped.";
			dialog.text = "Geminin kasasına hâlâ otuz peso borcun var — bozduğun yağmur fıçısı için. Gömleğini yıkama girişimin o kadar komikti ki, tam o sırada tekrar yağmur yağmasaydı sana daha da pahalıya patlayacaktı. "+sStr+"";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass"))
			{
				if (sti(pchar.Money) >= 230)
				{
					link.l1 = "Tam da ihtiyacım olan şey — daha gemiden iner inmez borçlar. Al bakalım.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			else
			{
				if (sti(pchar.Money) >= 30)
				{
					link.l1 = "Tam da ihtiyacım olan şey — daha gemiden iner inmez borçlar. Al bakalım.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			link.l2 = "Hepsi bu mu? Bu bir kumar borcu değil. Şu an biraz meşgulüm — limana yanaşana kadar beklemen gerekecek.";
			link.l2.go = "OfficerKaznachey_3_1";
		break;

		case "OfficerKaznachey_3_1":
			dialog.text = "Yazık. Peki o zaman — sadede gelelim. Sana bir görevim var.";
			link.l1 = "Pek de insan canlısı sayılmazsın, değil mi?";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_4":
			dialog.text = "Bir dakika, saymama izin ver.";
			link.l1 = "Akşam yemeğinden sonra masada bıraktığım ekmek kırıntılarını saymayı unutma.";
			link.l1.go = "OfficerKaznachey_5";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddMoneyToCharacter(pchar, -230);
			else AddMoneyToCharacter(pchar, -30);
		break;
		
		case "OfficerKaznachey_5":
			dialog.text = "Tebrikler. Gemi hazinesi artık sana soru sormayacak. Şimdilik.\nKısa kesiyorum — sana bir görevim var.";
			link.l1 = "Pek insanlarla aranın iyi olduğu söylenemez, değil mi?";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_6":
			dialog.text = "İnsanlarla mı? Pek sayılmaz. Ama sayılarla aram iyidir.\nPeki ya siz, monsieur "+pchar.lastname+" — saymayı biliyor musun?";
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				link.l1 = "(Muhasebeci) Defterlere ya da poliçelere yabancı değilim. Hatta sıfırın ne anlama geldiğini bile bilirim.";
				link.l1.go = "OfficerKaznachey_7";
			}
			else
			{
				link.l1 = "Babamın kıt harçlığını sezon boyunca idare etmeye yetecek kadar.";
				link.l1.go = "OfficerKaznachey_8";
			}
		break;

		case "OfficerKaznachey_7":
			dialog.text = "Ooooh! Keşke bana daha önce söyleseydin – bu yolculuk çok daha ilginç olabilirdi.";
			link.l1 = "Bir işten mi bahsettiniz?";
			link.l1.go = "OfficerKaznachey_9";
		break;

		case "OfficerKaznachey_8":
			dialog.text = "Kendi iyiliğin için, umarım asla bir gemi sahibi olmazsın. Hem kendini hem de gemidekilerin hepsini batırırsın.";
			link.l1 = "Bir görevden mi bahsettiniz?";
			link.l1.go = "OfficerKaznachey_9";
		break;
		
		case "OfficerKaznachey_9":
			dialog.text = "Evet. Farkında mısın bilmiyorum ama gemi katibiyle doktor, kaptandan sonra en yetkili kişilerdir.\n"+"İkisinden biri olmadan denize açılmak, paranı riske atmak demektir. Para olmadan ise bir gemi sadece çok pahalı bir tahta parçasıdır.\n"+"Bir gemi katibi olmadan, küçük bir şalopa bile kaptanını iflasa sürükleyebilir. Ve ilk çatışmada bir doktor yoksa, tüm mürettebatı kaybedebilirsin — ardından yerlerine yenilerini bulup eğitmek uzun ve pahalı bir sürece dönüşür.\n"+"Neyse ki, ikimiz için de ben ikisini de yapıyorum. Bu da bana mürettebattan kişisel alışveriş yapma ve küçük hizmetler isteme imkânı veriyor.\n"+"Elbette, cömertçe öderim — ve şimdi bunun için iyi bir zaman.\n"+"Bu listeyi, bu altın dolu sandığı almanı ve mürettebata ödeme yapmanı istiyorum.\n"+"Aynen listelendiği gibi! Bu yüzden sayıp sayamayacağını sordum.";
			link.l1 = "Neden kendin yapmıyorsun? Eğer ödeme bekliyorlarsa — bırak sana gelsinler.";
			link.l1.go = "OfficerKaznachey_10";
		break;
		
		case "OfficerKaznachey_10":
			dialog.text = "Şu anda yapacak çok iş var. Yolculuğun bitmesine sadece birkaç gün kaldı — yakında yüzlerce denizci maaşını istemek için sıraya girecek.";
			link.l1 = "Altınlardan bahsettiniz...";
			link.l1.go = "OfficerKaznachey_11";
		break;

		case "OfficerKaznachey_11":
			dialog.text = "İspanyol altın parası. Sert para birimi. Zenginliğin gerçek ölçüsü. Sadece en nadir ve değerli hizmetler bununla ödenir.\nBunlar, kolaylık olsun diye böyle sandıklarda saklanır.";
			link.l1 = "Peki, ben bundan ne kazanacağım?";
			link.l1.go = "OfficerKaznachey_12";
		break;

		case "OfficerKaznachey_12":
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				dialog.text = "(Muhasebeci) 150 peso ve 5 ekstra dublon — neredeyse meslektaşım olduğun için. Ayrıca peso ile dublon arasında adil bir kurdan faydalanacaksın.";
			}
			else
			{
				dialog.text = "150 peso ve pesoları dublona çevirebilme imkânı. Çok değil, ama iş de basit.";
			}
			link.l1 = "Pekala. Listeyi ve sandığı ver.";
			link.l1.go = "OfficerKaznachey_11_agree";
			link.l2 = "Böyle bir işin bana göre olmadığından korkuyorum. Elveda, Mösyö Pinchon.";
			link.l2.go = "OfficerKaznachey_11_otkaz";
		break;
		
		case "OfficerKaznachey_11_otkaz":
			dialog.text = "Senin seçimin. Sadece yolumdan çekil, monsieur "+pchar.lastname+"";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
		break;

		case "OfficerKaznachey_11_agree":
			if(GetItemsWeight(pchar) + sti(Items[GetItemIndex("Chest")].weight) > GetMaxItemsWeight(pchar))
			{
				dialog.text = "Al bakalım. Allah aşkına — sandıktaki doblonları almayı unutma, listeye harfiyen uy ve fazladan bir şey cebine atayım deme. Boş sandığı da geri bekliyorum.\nKendini fazla yorma, monsieur. Neden bu kadar ıvır zıvır taşıyorsun? Bir kısmını sandığa koymanı tavsiye ederim.";
			}
			else
			{
				dialog.text = "Al bakalım. Allah aşkına — sandıktaki doblonları almayı unutma, listeye harfiyen uy, fazladan bir kuruş bile cebe atayım deme. Sandığı da boş olarak geri bekliyorum.";
			}
			link.l1 = "Dediğiniz gibi olsun. Yakında görüşürüz, Mösyö Pinchon.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_QuestRazdatZoloto");
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "1");
			else AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "2");
			GiveItem2Character(PChar, "chest");
			if (!isMultiObjectKnown("gold_dublon"))
			{
				SetAlchemyRecipeKnown("gold_dublon");
				SetAlchemyRecipeKnown("Chest");
			}
		break;
				
		case "OfficerKaznachey_12_Wait":
			dialog.text = "Nasıl geçti? Hepsine ödedin mi? Kalan doblonlar ve boş sandık yanında mı?";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuest") && sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) == 3 && CheckCharacterItem(PChar, "chest_open") && PCharDublonsTotal() >= 18)
			{
				link.l1 = "Hepsi tamam.";
				link.l1.go = "OfficerKaznachey_13";
			}
			link.l2 = "Henüz değil, Mösyö Pinchon.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerKaznachey_12_Wait";
		break;

		case "OfficerKaznachey_13":
			dialog.text = "Bakalım...";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_14";
		break;

		case "OfficerKaznachey_14":
			addGold = PCharDublonsTotal();
			if (addGold >= 18 && addGold <= 39)
			{
				dialog.text = "Ve saymayı bildiğini iddia ettin. Beklenenden daha az dublon getirdin. Bu da bana daha fazla iş çıkarıyor, az değil — ve bu da sana ödeme yok demek.";
				link.l1 = "Ama yine de doblon bozar mısınız?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold >= 41)
			{
				dialog.text = "Ve saymayı bildiğini iddia ediyordun. Gerekenden fazlasını getirmişsin. Bu da bana fazladan iş çıkarıyor, az değil — yani sana ödeme yok.";
				link.l1 = "Takasa ne dersin?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold == 40)
			{
				if (IsCharacterPerkOn(pchar, "HT2"))
				{
					dialog.text = "Her şey doğru. Genç neslin hâlâ sayabildiğini görmek güzel. Teşekkür ederim, monsieur "+pchar.lastname+". İşte paran — ve bir de küçük bir ikramiye, bir profesyonelden diğerine.";
					link.l1 = "Ve takas?";
					link.l1.go = "OfficerKaznachey_15_gold_100";
					AddItems(pchar, "gold_dublon", 5);
				}
				else
				{
					dialog.text = "Her şey tamam. Gençlerin paraya sorumlulukla yaklaşmasını görmek güzel. Teşekkür ederim, monsieur "+pchar.lastname+". İşte ödemeniz.";
					link.l1 = "Hâlâ takas mı yapıyorsun?";
					link.l1.go = "OfficerKaznachey_15_gold_105";
				}
				AddMoneyToCharacter(pchar, 300);
				AddCharacterSkillPoints(pchar, "Commerce", 1);
			}
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "chest_open");
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", 100);
			pchar.questTemp.SharlieTutorial_KaznacheyQuestCompleted = true;
			DeleteAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive");
			npchar.Merchant.type = "SharlieTurorialK";
			pchar.SharlieTutorial.FullyCompleted = sti(pchar.SharlieTutorial.FullyCompleted) + 1;
		break;
		
		case "OfficerKaznachey_15_gold_115":
			dialog.text = "Neden olmasın. 115 peso bir dublon için. İlgilenirsen gel bana.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 115;
		break;

		case "OfficerKaznachey_15_gold_105":
			dialog.text = "Elbette. Her doubloon için 105 peso. İlgilenirsen bana gel.\nSana bir tavsiye vereyim: kader seni bir gün bir geminin başına geçirirse, ilk iş olarak bir veznedar tut. Kötü biri bile sana servet kazandırır.";
			link.l1 = "Teşekkür ederim, Mösyö Pinchon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 105;
		break;

		case "OfficerKaznachey_15_gold_100":
			dialog.text = "Elbette! Her doubloon için 100 peso — gayet makul bir oran. Karayip bankaları senden daha fazlasını alırdı.\nSana bir tavsiye vereyim: kaderin seni bir gün bir geminin başına geçirirse, ilk iş olarak bir veznedar tut. Kötüsü bile sana servet kazandırır.";
			link.l1 = "Teşekkür ederim, Mösyö Pinchon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 100;
		break;
		
		case "OfficerKaznachey_16_Proval": // Если не выполнил задание, то отбирает дублоны
			dialog.text = "Ortalıkta aylak aylak dolaşıyorsun, monsieur "+pchar.lastname+"?";
			link.l1 = "Sen de mi ambaraya verildin?";
			link.l1.go = "OfficerKaznachey_16_Proval_2";
		break;
		
		case "OfficerKaznachey_16_Proval_2":
			dialog.text = "Ben geminin doktoruyum, "+pchar.lastname+"!   Birazdan kamaralar yaralılarla dolacak ve ben, en az bir savaşçı kadar kan göreceğim. Ve diyelim ki sadece gemi katibiyim, yine de ateş hattındaki yerimi alırım. Hayır, rahat ambarında dinlenmeye gönderilen tek kişi sensin.";
			link.l1 = "O halde burada ne işin var?";
			link.l1.go = "OfficerKaznachey_16_Proval_3";
		break;
		
		case "OfficerKaznachey_16_Proval_3":
			dialog.text = "Savaş birkaç saat daha başlamayacak, bu yüzden günlük hesapları kapatmak için en uygun zaman. Altın sandığım sende, de Maure. Lütfen geri ver onu.";
			if (PCharDublonsTotal() >= 1 || GetCharacterItem(pchar, "chest") >= 1 || GetCharacterItem(pchar, "chest_open") >= 1)
			{
				link.l1 = "Al bunu. Ve bir daha buralarda yüzünü gösterme.";
				link.l1.go = "OfficerKaznachey_16_Proval_4";
			}
			else
			{
				link.l1 = "Eşyalarını başka bir yere bıraktım.";
				link.l1.go = "OfficerKaznachey_16_Proval_5";
			}
		break;
		
		case "OfficerKaznachey_16_Proval_4":
			addGold = PCharDublonsTotal();
			dialog.text = "Bunu hiç istemedim. Ben bir kara faresiyim diye düşünme – yerim ambar değil. Elveda.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			if (PCharDublonsTotal() >= 1 || GetCharacterItem(pchar, "chest") >= 1) ChangeCharacterComplexReputation(pchar, "nobility", -3);
			else ChangeCharacterComplexReputation(pchar, "nobility", -6);
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", addGold);
			TakeItemFromCharacter(pchar, "chest");
			TakeItemFromCharacter(pchar, "chest_open");
		break;
		
		case "OfficerKaznachey_16_Proval_5":
			dialog.text = "Başka bir yerde... Bunu savaştan sonra, kaptanın huzurunda konuşacağız. O zamana kadar.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
		break;
		
		case "TreasurerTrade":
			dialog.text = "Altınlara mı göz diktiniz, monsieur "+pchar.lastname+"?";
			link.l1 = "Bir anlaşma yapalım.";
			link.l1.go = "TreasurerTrade_1";
			link.l2 = "Şu anda değil.";
			link.l2.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
		break;
		
		case "TreasurerTrade_1":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "TreasurerTrade";
		break;
		// <-- Диалог с офицером-казначеем
		
		// --> Матрос сообщает о приближающихся кораблях
		case "Sailor_Trevoga":
			dialog.text = "Kaptan, alarm! Ufukta korsanlar var!";
			link.l1 = "...";
			link.l1.go = "Sailor_Trevoga_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain"));
			PlaySound("Ship\rynda_alarm.wav");
		break;

		case "Sailor_Trevoga_2":
			StartInstantDialog("SharlieTutorial_Captain", "Sailor_Trevoga_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "Sailor_Trevoga_3":
			dialog.text = "Alonso, lütfen Mösyö'ye eşlik et "+pchar.lastname+" ambarlara götürün. Ve Drussac Bey’in uyanık olduğundan ve topçuların hazır bulunduğundan emin olun.";
			link.l1 = "Kaptan, savaşmaya hazırım! Bir soylu asla...";
			link.l1.go = "Sailor_Trevoga_4_fencing";
			link.l2 = "Eğer bir şekilde yardımcı olabilirim...";
			link.l2.go = "Sailor_Trevoga_4_leadership";
			link.l3 = "Bekle, bu durumda Burgundy de yok mu?..";
			link.l3.go = "Sailor_Trevoga_4_fortune";
		break;

		case "Sailor_Trevoga_4_fencing":
			dialog.text = "Alonso, çıkarın onu buradan. Hadi, tembeller! Yelkenleri kaldırın!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "Sailor_Trevoga_4_leadership":
			dialog.text = "Alonso, çıkarın şunu buradan. Hadi, tembeller! Yelkenleri kaldırın!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "Sailor_Trevoga_4_fortune":
			dialog.text = "Alonso, çıkarın onu buradan. Hadi, tembeller! Yelkenleri kaldırın!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
				// <-- Матрос сообщает о приближающихся кораблях
				
				// --> Диалог с пиратом в трюме
		case "EnemyPirate_1":
			dialog.text = "Lanet olsun! Ne inatçı herifler!";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_2";
			//PlaySound("VOICE\Spanish\OliverTrast01.wav"); //вставить для испанской версии
			PlaySound("interface\abordage.wav");
			PlaySound("interface\abordage.wav");
		break;

		case "EnemyPirate_2":
			dialog.text = "Ve sen burada ne yapıyorsun?! Mürettebatını bırakıp kavgadan mı kaçıyorsun, pis fare?! Şimdi seni burada doğrarım!";
			link.l1 = "Ambarıma sızmakla kötü bir iş yaptın. Seni bizzat ben geberteceğim.";
			link.l1.go = "EnemyPirate_3_Fencing";
			link.l2 = "Zar zor ayakta duruyorsun, üzerindeki kanın çoğu da sana ait değil zaten.";
			link.l2.go = "EnemyPirate_3_Leadership";
			if (IsCharacterPerkOn(pchar, "HT1"))
			{
				link.l3 = "(Düellocu) Bunu ne kadar özlemişim.";
				link.l3.go = "EnemyPirate_3_Duelyant";
			}
		break;

		case "EnemyPirate_3_Fencing":
			dialog.text = "Heh-heh. Devam et bakalım, süslü.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "EnemyPirate_3_Leadership":
			dialog.text = "Heh-heh. O zaman kaybedecek bir şeyim yok.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "EnemyPirate_3_Duelyant":
			dialog.text = "Ne saçmalıyorsun sen?!";
			link.l1 = "İki ay. İki ay boyunca kılıcımı kınında tuttum. Hadi dans edelim!";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "EnemyPirate_4":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_2");
		break;
		
		// <-- Диалог с пиратом в трюме
		
		// --> Диалог с выжившим матросом
		case "SailorAlive_1":
			dialog.text = "En azından hayattasın... Ben bittim. Dümen başında fena darbe aldım...";
			link.l1 = "Ne oldu?!";
			link.l1.go = "SailorAlive_2";
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_2":
			dialog.text = "Bize baskın yaptılar. Kahretsin! İnatçı herifler!\nİyi dinle: Top güvertesini tuttuk ama asıl eğlence yukarıda başlıyor. Yemin ederim, her an aşağı inebilirler. Al bu saçmalı tüfeği! Dikkat et, şeytan! Dolu o!";
			if (IsCharacterPerkOn(pchar, "HT4"))
			{
				link.l1 = "(Keskin nişancı) Benim için endişelenme. Bana bulaşan herkesi delik deşik ederim.";
			}
			else link.l1 = "...";
			link.l1.go = "SailorAlive_3";
		break;

		case "SailorAlive_3":
			dialog.text = "İçinde saçma var. Doğru yaparsan, bir seferde iki ya da üç tanesini indirebilirsin.\nSana güveniyorum, "+pchar.name+". Onlarla işin bittikten sonra, cesetleri kontrol et. Belki bana bir içki bulursun... yoksa sana yardım edemem.";
			link.l1 = "Dayan Alonso. Misafirler geliyor!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_5");
			GiveItem2Character(PChar, "pistol3");
			EquipCharacterByItem(PChar, "pistol3");
			AddItems(pchar, "grapeshot", 5);
			AddItems(pchar, "GunPowder", 5);
			LAi_GunSetChargeQuant(pchar, GUN_ITEM_TYPE, 1);
		break;

		case "SailorAlive_11":
			dialog.text = "Pekala... İyi iş çıkardın, "+pchar.name+" . Benim için bir şey bulabildin mi?";
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				link.l1 = "Bence burası. Ama biraz şüpheli görünüyor.";
				link.l1.go = "SailorAlive_12";
			}
			link.l2 = "Hâlâ bakıyorum!";
			link.l2.go = "exit";
			NextDiag.TempNode = "SailorAlive_11";
		break;

		case "SailorAlive_12":
			dialog.text = "Hiç fena değil, ha-ha! Teşekkürler, "+pchar.name+". Ve şu üç kişiyi — güzelce indirdin. Gerçekten asilzade olduğuna göre, komutayı sen al. Birlikte bu güvertede durabiliriz. Yukarıdakiler de başarırsa — gün bizim olur!";
			link.l1 = "...";
			//link.l1.go = "exit";
			link.l1.go = "SailorAlive_13";
			//AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_7");
			TakeItemFromCharacter(pchar, "quest_potion");
			PlaySound("Ambient\Tavern\glotok_001.wav");
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_13":
			/*if (CheckAttribute(npchar, "fighter"))
			{
				dialog.text = "Çok daha iyi. Saçmalı tüfeği doldurdun mu?";
				link.l1 = "Sadece onu yapıyorum... Neden birdenbire bu kadar sessiz oldu?";
				link.l1.go = "SailorAlive_14";
				SetMusic("");
			}
			else
			{
				dialog.text = "Gerçekten bir soylu olduğuna göre, komutayı devral.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "SailorAlive_13";
			}*/
			dialog.text = "Çok daha iyi. Saçmalı tüfeği doldurdun mu?";
			link.l1 = "Sadece bunu yapıyorum... Neden birdenbire bu kadar sessiz oldu?";
			link.l1.go = "SailorAlive_14";
			SetMusic("");
			LAi_SetActorType(npchar);
			LAi_ActorSetGroundSitMode(npchar);
			LAi_ActorAnimation(npchar, "ground_standup", "1", -1);
		break;

		case "SailorAlive_14":
			dialog.text = "Sadece biraz daha dram olsun diye. Az sonra başlayacak.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_8");
		break;
		// <-- Диалог с выжившим матросом
		
		// --> Диалог с Алонсо после боя
		case "AfterBattle_Alonso_1":
			dialog.text = "İşte buradayız, başladığımız yere geri döndük. Beni kurtardığın için sağ ol, "+pchar.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_Ranen"))
			{
				link.l1 = "Sanırım artık ödeşmiş olduk. Oradan beni nasıl çıkardığını bile hatırlamıyorum.";
			}
			else
			{
				link.l1 = "Sanırım artık ödeşmiş olduk. Sen ve çocuklar olmasaydınız, hâlâ orada olurdum.";
			}
			link.l1.go = "AfterBattle_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "AfterBattle_Alonso_2":
			dialog.text = "Emir edildiği gibi ambarın içinde kalabilirdin. Ne yazık ki kaptan sana hak ettiğin azarı vermeye yaşamadı.";
			link.l1 = "Onu cesetlerin altından çıkarmak zorunda kaldık. Kaç tane alçağı hakladı?";
			link.l1.go = "AfterBattle_Alonso_3";
		break;

		case "AfterBattle_Alonso_3":
			dialog.text = "Kimisi onun üç kişiyi yere serdiğini gördü. Kimisi bir düzine diyor. Bence sayıyı yalnızca şeytan biliyor.";
			link.l1 = "Bana hala her şeyin nasıl bu hale geldiğini anlatmadın.";
			link.l1.go = "AfterBattle_Alonso_4";
		break;

		case "AfterBattle_Alonso_4":
			dialog.text = "Anlatacak ne var ki? On altı librelik toplarımız bir tane bile korsan briginden bizi kurtaramadı.\n"+"Bir anda üstümüze çullandı, dönüşte üzerimize saçma yağdırdı ve hemen gemiye çıktı. Güvertede görecek bir şey kalmamıştı — cerraha iş düşmedi bile.\n"+"Korsanlarla savaşmanın en kötü yanı — hiç kâr yok. Sadece beş parasızlar. Briklerini bile alamadık.";
			link.l1 = "Sırada ne olacak?";
			link.l1.go = "AfterBattle_Alonso_5";
		break;

		case "AfterBattle_Alonso_5":
			dialog.text = "Gemi su üstünde, ve seni tam zamanında Saint-Pierre’e götürecek kadar adamımız kaldı. Orada ben yeni bir kaptan arayacağım, sen de kardeşini bulup başından geçenleri anlatacaksın. Sonrasıysa — onu ancak Tanrı bilir.\n"+"Ama bir şey kesin - bizimle gayet iyi uyum sağlayacaksın. Kara faresi için fena değil, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "AfterBattle_Alonso_6";
		break;

		case "AfterBattle_Alonso_6":
			dialog.text = "Ha! Birazdan için dışına çıkacak. Çekinme. Bu sadece korkunun bedenini terk etmesi. Karayiplere hoş geldin!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_SeaNearMartinique");
		break;
		
		// <-- Диалог с Алонсо после боя
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}