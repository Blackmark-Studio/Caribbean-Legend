void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Ne istiyorsunuz?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";
		break;
		
		// Квест "Длинные тени старых грехов"
		case "DTSG_Knippel_1":
			dialog.text = "Ah, bugün ne sıcak. Şu bunaltıdan kurtulmak için bacağına zincirli gülle bağlayıp denize atlayası geliyor insanın!";
			link.l1 = "Ha-ha, Charlie!.. Bunlar biraz aşırı önlemler, bana sorarsan. Ama şöyle bir boğazımı ıslatsam fena olmazdı – bugün gerçekten çok sıcak. Var mısın?";
			link.l1.go = "DTSG_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Knippel_2":
			dialog.text = "Sizinle bir iki kadeh içmek mi, Kaptan? Her zaman!";
			link.l1 = "İşte duymak istediğim bu. Hadi gidelim!";
			link.l1.go = "DTSG_Knippel_3";
		break;
		
		case "DTSG_Knippel_3":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_1");
		break;
		
		case "DTSG_Ohotnik_1":
			dialog.text = "Hey, denizci, her şeyi görmüş gibisin! Hadi bir içki içelim, hikayelerimizi paylaşalım? Benden olsun!";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_1_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
			
		break;
		
		case "DTSG_Ohotnik_1_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_2":
			dialog.text = "Yok, sağ ol dostum. Ben buraya Kaptanımla geldim. Başkasını bul.";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_2_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
			locCameraFromToPos(5.57, 2.39, -4.63, true, 8.53, 2.07, 1.84);
		break;
		
		case "DTSG_Ohotnik_2_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_3", "Quest\CompanionQuests\Knippel.c");
			locCameraSleep(true);
		break;
		
		case "DTSG_Ohotnik_3":
			dialog.text = "Ha, senin gibi bir serseri kendini ne sanıyor da sadece kaptanlarla içiyor?";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_3_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_3_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_4", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_4":
			dialog.text = "Yüksek fikirler mi?! Onlarca yıl Kraliyet Donanması’nda hizmet ettim! Ve ben lordlar için değil, senin ve benim gibi sıradan insanlar için savaştım, her yerde hukuk ve düzen olsun diye!..";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_4_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_4_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_5", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_5":
			dialog.text = "Büyük laflar ediyorsun, ama sadece kaptanlarla ve soylularla içiyorsun! Görünen o ki, Donanma sana topları parlatmayı gerçekten öğretmiş, ha!";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_5_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_5_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_6":
			dialog.text = "Zincirli gülleyi boğazından aşağı tıkarım, velet!";
			link.l1 = "Charlie, bu kadar telaşlanma, buna değmez.";
			link.l1.go = "DTSG_Ohotnik_7";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_7":
			dialog.text = "Bunu bana bırak, Kaptan. Donanmanın onuru söz konusu, onu kendim savunmalıyım, kimsenin arkasına saklanamam...";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_8";
		break;
		
		case "DTSG_Ohotnik_8":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Ohotnik_DlgExit_1");
		break;
		
		case "DTSG_Knippel_l0":
			dialog.text = "Beklediğiniz için teşekkür ederim, Kaptan. Umarım fazla oyalamadım.";
			link.l1 = "Boşver onu. İyi misin, bir yerin incinmedi mi? O alçak bayağı iyiydi.";
			link.l1.go = "DTSG_Knippel_l1";
		break;
		
		case "DTSG_Knippel_l1":
			dialog.text = "Canını sıkma, Kaptan. Önemli olan, hak ettiğini buldu. Üzerinden bir çeşit anahtar aldım...";
			link.l1 = "...";
			link.l1.go = "DTSG_Knippel_l2";
		break;
		
		case "DTSG_Knippel_l2":
			dialog.text = "Adamın üzerinden bir çeşit anahtar buldum... Acaba ne işe yarıyor?";
			link.l1 = "Çok basit, Charlie... Bir kapı ya da sandık için, ha-ha. Bu herif hakkında han sahibiyle konuşmalıyız, işimize yarayabilir.";
			link.l1.go = "DTSG_Knippel_l3";
			AddItems(pchar, "Key1", 1);
			Log_info("Charlie gave you the key.");
			PlaySound("interface\important_item.wav");
		break;
		
		case "DTSG_Knippel_l3":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_2");
		break;
		
		case "DTSG_Knippel_20":
			dialog.text = "İnanılmaz...";
			link.l1 = "Benim aklımdan geçenleri mi düşünüyorsun, Charlie?";
			link.l1.go = "DTSG_Knippel_21";
		break;
		
		case "DTSG_Knippel_21":
			dialog.text = "Bilmem siz ne düşünürsünüz efendim, ama burada bu kadar para olmasına şaşırdım – adam sıradan biri gibi görünüyordu, ne bir tüccara ne de bir soyluya benziyordu.";
			link.l1 = "Gerçekten o kadar da fazla değil, ama haklısın. Beni asıl şaşırtan ise şu garip yanık mektup.";
			link.l1.go = "DTSG_Knippel_22";
		break;
		
		case "DTSG_Knippel_22":
			dialog.text = "Evet, bu pek akıllıca değildi – sağlam bir gövdeye zincir gülle atmak gibi. Mektubu tamamen yok etmeliydi.";
			link.l1 = "Doğru. Ama bu bize bir fayda sağlamıyor - kim olduğunu ya da kiminle yazıştığını bilmiyoruz. Hadi gidelim Charlie, burada işimiz bitti.";
			link.l1.go = "DTSG_Knippel_23";
		break;
		
		case "DTSG_Knippel_23":			//КОНЕЦ ЭТАПА 1
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_2_1");
		break;
		
		case "DTSG_Ohotnik_10":
			dialog.text = "Senin o övündüğün Kraliyet Donanması da bu kadar işte, pöh!";
			link.l1 = "Charlie iyi, dürüst bir adamdı. Ve o bir topçu subayıydı, deniz piyadesi değil.";
			link.l1.go = "DTSG_Ohotnik_11";
		break;
		
		case "DTSG_Ohotnik_11":
			dialog.text = "Bir topçu muymuşum?! Yani, tam da dediğim gibiymiş, ha-ha-ha! Ve öyle dik dik bakma – kimi tayfana aldığını baştan bilmeliydin.";
			link.l1 = "Kiminle uğraştığını bilmeliydin.";
			link.l1.go = "DTSG_Ohotnik_Agressia_1";
			link.l2 = "Sadece adil bir şekilde kazandığın için hâlâ hayattasın, o yüzden o çürük dilini tut ve defol buradan.";
			link.l2.go = "DTSG_Ohotnik_Otpustil_1";
		break;
		
		case "DTSG_Ohotnik_Otpustil_1":
			dialog.text = "Doğrusu, bir sonraki dövüşüm seninle olacak sanmıştım. Onur senin için bir anlam ifade ediyor olması güzel.";
			link.l1 = "Charlie için de sadece boş laflar değildi. Ama sana gelince, şüphelerim var. Neyse, artık önemi yok.";
			link.l1.go = "DTSG_Ohotnik_Otpustil_2";
		break;
		
		case "DTSG_Ohotnik_Otpustil_2":			//ПРОВАЛ ЭТАПА 1
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Ohotnik_DlgExit_2");
		break;
		
		case "DTSG_Ohotnik_Agressia_1":
			dialog.text = "Ve ben kimi kızdırdım, şımarık bir zayıfı mı?! Kendi ince bıyığını hiç gördün mü?..";
			link.l1 = "Düğmelere basmayı iyi biliyorsun... Öfkemi senden çıkarmak daha da tatmin edici olacak.";
			link.l1.go = "DTSG_Ohotnik_Agressia_2";
		break;
		
		case "DTSG_Ohotnik_Agressia_2":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Ohotnik_DlgExit_3");
		break;
		
		case "DTSG_PiterAdams_1":
			dialog.text = "Bekleyin, Kaptan. Sizin değerli ve onurlu bir insan olduğunuzu görüyorum, bana bir konuda yardımcı olur musunuz? Bu bir onur meselesi.";
			link.l1 = "Belki yapabilirim, ama mesele nedir? Ve neden bana geldiniz? Burada birçok soylu insan var. Bu arada, kiminle konuşma şerefine nail oldum?";
			link.l1.go = "DTSG_PiterAdams_2";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "DTSG_PiterAdams_2":
			dialog.text = "Peter. Peter Adams. Görüyorum ki sen eski bir ailenin şımarık torunlarından değilsin, aksine güvenilir ve sağlam bir adamsın.";
			link.l1 = "Ah, Karayipler'e ilk geldiğim zamanı görmeliydiniz, efendim. Neyse, söyleyin bakalım, neye ihtiyacınız var?";
			link.l1.go = "DTSG_PiterAdams_3";
		break;
		
		case "DTSG_PiterAdams_3":
			dialog.text = "Benim için düello edebilir misiniz, efendim? Buradaki bir serseri, Ralph Faggle, eşime hakaret etti. Üstelik onu herkesin önünde taciz etti. Hem de gözümün önünde. Bunu hayal edebiliyor musunuz?";
			link.l1 = "Bir düelloya meydan okuyup sonra başkasının arkasına saklanmakta pek bir onur yok. Hele ki mesele sadece senin kişisel onurun değil, bir kadının, hem de karının onuru söz konusuyken. Sence de öyle değil mi, Adams? Kendi kadının için neden kendin savaşamıyorsun?";
			link.l1.go = "DTSG_PiterAdams_4";
		break;
		
		case "DTSG_PiterAdams_4":
			dialog.text = "Haklısın, tamamen haklısın. Ama yakın zamanda ağır bir ateş geçirdim, ayakta zor duruyorum\nAçıkçası, senden böyle bir şey istemek bana hiç kolay gelmiyor. Bana hakaret etseydi, sineye çekerdim. Ama söz konusu olan karımın onuruysa, iş değişir! Ben korkak değilim, efendim. Bir zamanlar Kraliyet Donanması'nda hizmet ettim ve bizzat Robert Blake ile aynı gemide yol aldım!";
			link.l1 = "Ben...";
			link.l1.go = "DTSG_PiterAdams_5";
		break;
		
		case "DTSG_PiterAdams_5":
			StartInstantDialog("Knippel", "DTSG_PiterAdams_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_6":
			dialog.text = "Sana yardım edeceğiz.";
			link.l1 = "Charlie?..";
			link.l1.go = "DTSG_PiterAdams_7";
			CharacterTurnByChr(npchar, characterFromId("DTSG_PiterAdams"))
		break;
		
		case "DTSG_PiterAdams_7":
			dialog.text = "O, değerli bir adamdır, Kaptan. Eğer bu doğru değilse, top gülleleriyle sonsuza dek lanetleneyim! Büyük insanlar Amiral Blake ile birlikte hizmet etti. Halkı ezmesinler diye omuz omuza savaştılar\nVe onun sayesinde, Jamaika İspanyolların zulmünden kurtuldu!";
			link.l1 = "Durum böyle olsa bile, tayfamın bana karışmasına ya da benim adıma karar vermesine izin vermem. Anlaşıldı mı?";
			link.l1.go = "DTSG_PiterAdams_8";
			link.l2 = "Anlıyorum, gerçekten. Ama daha cevap verme fırsatım bile olmadı. Lütfen bundan sonra bu kadar aceleci davranıp sözümü kesme, olur mu?";
			link.l2.go = "DTSG_PiterAdams_8";
			CharacterTurnByChr(npchar, pchar)
		break;
		
		case "DTSG_PiterAdams_8":
			dialog.text = "Sana şunu söyleyeyim Kaptan - eğer bu adama yardım etmezsen, yaşlı Charlie her şeyi bırakır ve onun için bizzat düelloya çıkar, burada çarpılayım!";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "Sessiz ol şimdi, yardım etmeyi reddettiğimi söylemedim. Öyle değil mi, Bay Adams?";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_1";
			}
			else
			{
				link.l1 = "Doğrusunu söylemek gerekirse, Charlie, beni korkak gibi gösteriyorsun. Oysa ben asla öyle biri olmadım. Bunu bilmelisin.";
				link.l1.go = "DTSG_PiterAdams_NN_1";
			}
		break;
		
		case "DTSG_PiterAdams_NN_1":
			dialog.text = "Affedersiniz, Kaptan, kendimi biraz kaptırdım.";
			link.l1 = "Sorun değil. Ama kendine hakim ol, tamam mı?";
			link.l1.go = "DTSG_PiterAdams_NN_1_1";
		break;
		
		case "DTSG_PiterAdams_NN_1_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_NN_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_NN_2":
			dialog.text = "";
			link.l1 = "Sizin için düelloya çıkarım, Bay Adams.";
			link.l1.go = "DTSG_PiterAdams_NN_3";
		break;
		
		case "DTSG_PiterAdams_NN_3":
			dialog.text = "Teşekkür ederim, efendim! Tanrı sizi korusun!";
			link.l1 = "Ve Lord Protector'a da dua edelim, değil mi Bay Adams? Merak etme, Charles de Maure dürüst bir adamı asla darda bırakmaz.";
			link.l1.go = "DTSG_PiterAdams_NN_4";
		break;
		
		case "DTSG_PiterAdams_NN_4":
			dialog.text = "Bunu gerçekten takdir ediyoruz, Bay de Maure, efendim! Jane ve benimle akşam yemeği yemek ister misiniz?";
			link.l1 = "Şey, ben...";
			link.l1.go = "DTSG_PiterAdams_NN_5";
		break;
		
		case "DTSG_PiterAdams_NN_5":
			dialog.text = "Israr ediyorum!";
			link.l1 = "Pekâlâ, madem ısrar ediyorsun. Teşekkür ederim, Peter. Yol göster.";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_Nastoroje_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_Nastoroje_2":
			dialog.text = "Elbette doğru, efendim! Jane ile birlikte gelip yolculuğunuzdan sonra biraz dinlenmek ister misiniz?";
			link.l1 = "Teşekkür ederim, ama misafirperverliğinizden faydalanmak doğru mu?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_3";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_3":
			dialog.text = "Tam tersine, Kaptan, gelmezseniz alınırız.";
			link.l1 = "O zaman nasıl reddedebilirdim? Önce sen, Peter!";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_IdemKDomu":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_3");
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_1":
			dialog.text = "Biziz! Lütfen, içeri gelin.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "Teşekkür ederim. Jane ile konuşabilir miyim? Ona nasıl olduğunu sor - tüm ayrıntılara ihtiyacım var.";
				link.l1.go = "DTSG_PiterAdamsRyadomSDomom_2";
			}
			link.l2 = "Çok özür dilerim, ama tekrar düşündüm ve reddetmek zorundayım. Önümde hazırlanmam gereken bir düello var. Bu arada, düello nerede ve ne zaman olacak?";
			link.l2.go = "DTSG_PiterAdamsRyadomSDomom_4";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_2":
			dialog.text = "Elbette efendim. İkimiz de sizinle konuşmaktan ve tüm sorularınızı yanıtlamaktan memnuniyet duyarız. Lütfen beni takip edin.";
			link.l1 = "Teşekkür ederim, Peter.";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_3";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_3":
			DoQuestReloadToLocation("PortPax_houseF1", "reload", "reload1", "DTSG_PiterAdams_VDom_2");
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_4":
			dialog.text = "Ne yazık! Ama haklısın, elbette iyice hazırlanmalısın. İki saat. Şehrin kapılarının hemen dışında.";
			link.l1 = "Anlaşıldı, teşekkür ederim. İşin bitince memnuniyetle gelirim. O zaman görüşürüz!";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_5";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_5":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_4");
		break;
		
		case "DTSG_JeinAdams_1":
			dialog.text = "Hoş geldiniz! Sevgili, misafir getireceğini söylemedin ki - ona göre hazırlanırdım.";
			link.l1 = "Teşekkür ederim hanımefendi, fazla oyalanmayacağız. Charles de Maure, hizmetinizdeyim. Eşinizle birlikte hikayenizi dinlemeyi kabul ettim. Anlatın, nasıl oldu?";
			link.l1.go = "DTSG_JeinAdams_2";
		break;
		
		case "DTSG_JeinAdams_2":
			dialog.text = "Ah, çok korkunçtu! Ralph tamamen sarhoştu. Komşuların önünde, hatta Peter'ın önünde bile bana sataşmaya başladı, ağzından ahlaksızca laflar dökülüyordu...";
			link.l1 = "Sana tam olarak ne söyledi?";
			link.l1.go = "DTSG_JeinAdams_3";
		break;
		
		case "DTSG_JeinAdams_3":
			dialog.text = "Bunu konuşmaya utanıyorum. Sonra ayıldı ve...";
			link.l1 = "Özür dileyip düelloyu iptal etmelerini mi istedin, yoksa?";
			link.l1.go = "DTSG_JeinAdams_4";
		break;
		
		case "DTSG_JeinAdams_4":
			dialog.text = "Bir kez bile değil.";
			link.l1 = "Sana üzülüyorum. Eğer izin verirseniz, hanımefendi, bir şey daha öğrenmek isterim.";
			link.l1.go = "DTSG_JeinAdams_5";
		break;
		
		case "DTSG_JeinAdams_5":
			dialog.text = "Ve o nedir, efendim?";
			link.l1 = "Sizi ve kocanızı burada yaşamaya iten hayat şartları ve zorluklar neydi? Kocanızın meziyetleriyle, İngiltere'nin herhangi bir şehrinde Ralph'ı çoktan hizaya sokardınız.";
			link.l1.go = "DTSG_JeinAdams_6";
		break;
		
		case "DTSG_JeinAdams_6":
			StartInstantDialog("Knippel", "DTSG_JeinAdams_7", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_7":
			dialog.text = "Affedersiniz efendim, ama siz nasıl cüret edersiniz?! Kaptanım olmasaydınız, zincir gülleyle sizi güzelce pataklardım!\nHem Bay Adams gibi değerli bir adama güvenmiyorsunuz, hem de zor durumdaki bir hanımla alay ediyorsunuz...";
			link.l1 = "Bir hanımefendiyle alay ettiğimi duydun mu? Hayır? O zaman bana iftira atma. Bizim insanlarımız onlara yardım edebilirdi, bu yüzden sordum.";
			link.l1.go = "DTSG_JeinAdams_8a";
			link.l1 = "Sakin ol, Charlie! Nasıl böyle düşünebilirsin... Ben sadece Jane ve Peter'ın yaşadıklarını daha iyi anlamak ve onlara biraz olsun destek olmak istedim. İngiliz kolonilerinde olsalardı, şimdiye kadar mutlaka yardım edilmiş olurdu.";
			link.l1.go = "DTSG_JeinAdams_8b";
		break;
		
		case "DTSG_JeinAdams_8a":
			dialog.text = "Hayat birçok şekilde değişebilir... Bir gemi kazası. Ya da birinin iftirası, ki bazen en dürüst insanları bile utanç içinde saklanmaya zorlar\nEğer bu kadar güvensiz ve kuşkucuysan - komşularla konuşabilirsin. Eminim söylediklerimin hepsini doğrulayacaklardır. Ama yaşlı Charlie, insanların acılarını arkalarından konuşacak kadar alçalmaz!";
			link.l1 = "Beni duymadın mı? Bu insanlara yardım edeceğimi söyledim.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
		break;
		
		case "DTSG_JeinAdams_8b":
			dialog.text = "Hayat insanı türlü hallere sokar... Bir gemi kazası. Ya da bazen en dürüst insanları bile utanç içinde saklanmaya zorlayan bir iftira\nEğer bu kadar kuşkucu ve güvensizsen - komşularla konuşabilirsin. Eminim söylediklerimi doğrularlar. Ama yaşlı Charlie, insanların acılarını arkalarından konuşacak kadar alçalmaz!";
			link.l1 = "Beni duymadın mı? Bu insanlara yardım edeceğimi söyledim.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", -2);
		break;
		
		case "DTSG_JeinAdams_9":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_JeinAdams_10", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_10":
			dialog.text = "Tüm kalbimizle teşekkür ederiz. Dualarımızda sizi anacağız.";
			link.l1 = "İyi. Bu arada, bizim meseleye gelirsek. Düelloyu nerede ve ne zaman ayarladınız, Bay Adams?";
			link.l1.go = "DTSG_JeinAdams_11";
		break;
		
		case "DTSG_JeinAdams_11":
			dialog.text = "Şehir kapılarının dışında, efendim. İki saat içinde.";
			link.l1 = "Başaracağım. Beni iyi haberlerle bekle. Ve sakın benim için erkenden mum yakmayı düşünme!";
			link.l1.go = "DTSG_JeinAdams_13";
		break;
		
		case "DTSG_JeinAdams_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "DTSG_PiterAdams_IsDoma");
		break;
		
		case "DTSG_Knippel_30":
			dialog.text = "Bir şey mi canınızı sıkıyor, Kaptan? Çok dalgın görünüyorsunuz.";
			link.l1 = "Biliyor musun, evet. Adams'ın hikayesinde bir tuhaflık var, ve...";
			link.l1.go = "DTSG_Knippel_31";
		break;
		
		case "DTSG_Knippel_31":
			dialog.text = "Bu daha ne kadar sürecek, efendim?! Birine yardım etmek gerektiğinde her seferinde böyle mi tepki veriyorsunuz?";
			link.l1 = "Tanrı aşkına, sessiz konuş. Bütün sokağa bağıracaksın neredeyse. Düelloya gideceğimi söyledim. Bu yetmiyor mu sana? Şimdi beni dikkatlice dinle.";
			link.l1.go = "DTSG_Knippel_32";
		break;
		
		case "DTSG_Knippel_32":
			dialog.text = "Hmm, peki, Kaptan. Bağırdığım için kusura bakmayın - Kraliyet Donanması'nda hizmet edenlerin kaderi benim için önemli. Birçoğumuz düzgün adamlardık, çoğumuzun yaşadığından daha iyi bir sonu hak ediyorduk.";
			link.l1 = "Seni anlıyorum, Charlie. Şimdi yapılması gerekeni unutma. Mürettebattan birkaç kişiyi şehir kapılarına göndermeni istiyorum. Düello vakti yaklaştıkça, sessizce toplanıp işaretimi beklesinler.";
			link.l1.go = "DTSG_Knippel_33";
		break;
		
		case "DTSG_Knippel_33":
			dialog.text = "Dürüst bir düelloyu cinayete mi çevirmeyi düşünüyorsun?";
			link.l1 = "Bunun tamamen dürüstçe olmayacağından şüpheleniyorum. Yalnızca gerekirse işaret vereceğim. Eğer her şey gerçekten düzgünse, yanılmış olmaktan memnun olurum. Şimdi anladın mı? Bir ay önce olanları hatırlıyor musun?";
			link.l1.go = "DTSG_Knippel_34";
		break;
		
		case "DTSG_Knippel_34":
			dialog.text = "Anlaşıldı, efendim. Açıkçası, bundan pek memnun değilim ama gerekeni yapacağım. Merak etmeyin.";
			link.l1 = "Duymak istediğim tam da buydu.";
			link.l1.go = "DTSG_Knippel_35";
		break;
		
		case "DTSG_Knippel_35":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_5");
		break;
		
		case "DTSG_RalfFaggl":
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			PChar.quest.DTSG_PoP_DuelTime.over = "yes";
			PChar.quest.DTSG_PoP_Duel.over = "yes";
			dialog.text = "Yani, de Maure. Erken geldin. Ve hâlâ şehirdeyiz. Gerçi fark etmez. Keşke o yaşlı budalayı da yanında getirseydin. Ama sorun yok, eninde sonunda ona da ulaşırız.";
			link.l1 = "Her zaman hizmetinizdeyim. Paralı asker misiniz? Kime bulaştım ben?";
			link.l1.go = "DTSG_RalfFaggl_2";
		break;
		
		case "DTSG_RalfFaggl_2":
			dialog.text = "İşte mesele bu, kimse değil. Biz o yaşlı herifin, Charlie'nin peşindeyiz ve öğrendiğimize göre artık senin gemindeymiş, bu yüzden seni bulmak daha kolay oldu. Burası orman değil, o yüzden kalabalık çekmeden hızlı davranmamız gerekecek. Ama burada, en azından, kaçamazsın.";
			link.l1 = "Sanırım bu düello meselesi baştan sona bir tuzaktı, değil mi?";
			link.l1.go = "DTSG_RalfFaggl_3";
		break;
		
		case "DTSG_RalfFaggl_3":
			dialog.text = "Bunu fark etmek için biraz geç kaldın, dostum. Yine de dövüşürdük – Ben Ralph Faggle, emrindeyim.";
			link.l1 = "Aslında, bundan şüpheleniyordum, bu yüzden komşularla konuşmaya karar verdim. Bu arada, Adams da bu işin içinde mi? Peki ya Jane? O da olabilir mi...";
			link.l1.go = "DTSG_RalfFaggl_4";
		break;
		
		case "DTSG_RalfFaggl_4":
			dialog.text = "Merakı kediyi öldürür, duymadın mı? Sana düelloya gelmen söylendi, etrafta burnunu sokman değil. Bu beladan sağ çıkma şansın olabilirdi\nTabii ya. Eski askeri kışkırt, sonra da komutanını düelloya zorla – işte Peter'la bulduğumuz harika plan bu, sanırım. Jane de kendi işini gayet iyi yaptı.";
			link.l1 = "Söyle bana, Charlie'den kim kurtulmak istedi?";
			link.l1.go = "DTSG_RalfFaggl_5";
		break;
		
		case "DTSG_RalfFaggl_5":
			dialog.text = "Ha, sana söyleyecekmişim gibi mi? Kendini savun.";
			link.l1 = "Yazık. O zaman Peter'a sonra sorarım.";
			link.l1.go = "DTSG_RalfFaggl_6";
		break;
		
		case "DTSG_RalfFaggl_6":
			DialogExit();
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetCheckMinHP(sld, 1, true, "DTSG_FrederikStouks_ranen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl");
			LAi_SetCheckMinHP(sld, 1, false, "DTSG_RalfFaggl_ubit");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_11":
			dialog.text = "Ah, demek hikayemi ciddiye aldınız ve Ralph'ı çoktan cezalandırdınız, Kaptan.";
			link.l1 = "Elbette, çünkü senin de belirttiğin gibi, ben değerli ve onurlu bir adamım. Ve şimdi, bu hain tuzak için seni cezalandırmam gerekecek.";
			link.l1.go = "DTSG_PiterAdams_12";
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			GiveItem2Character(npchar, "letter_1");
			ChangeItemName("letter_1", "itmname_specialletter");
			ChangeItemDescribe("letter_1", "itmdescr_DTSG_letter2");
		break;
		
		case "DTSG_PiterAdams_12":
			dialog.text = "Denemekte özgürsün, Kaptan - eminim zaten yorgun ve yaralısındır.";
			link.l1 = "O zaman biraz ara verelim. Bu arada, bana söyle, kimin için çalışıyorsun?";
			link.l1.go = "DTSG_PiterAdams_13";
		break;
		
		case "DTSG_PiterAdams_13":
			dialog.text = "Üzgünüm, ama hamim bundan hoşlanmazdı, sonrasında seninle başa çıksam bile. Bu arada, şimdi tam olarak öyle olacak.";
			link.l1 = "Lanet olsun!..";
			link.l1.go = "DTSG_PiterAdams_14";
		break;
		
		case "DTSG_PiterAdams_14":
			DialogExit();
			
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, GetCharacterBaseHPValue(sld)/2, GetCharacterBaseHPValue(sld));
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			else
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
				LAi_KillCharacter(sld);
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Sosedi_Pobeda");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_Knippel_40":
			dialog.text = "Şuna bak, bu... bu alçaklar hem bizi kandırdılar hem de Kraliyet Donanması hakkında yalan söylediler! Nasıl cüret ederler! Eğer hâlâ yaşıyor olsalardı, bu hainlikleri için onlara zincir güllelerini zorla yuttururdum!..";
			link.l1 = "İnsanlar her konuda yalan söyler, Charlie. Bunu iyi bildiğini sanıyordum. Ama kesin bildiğin bir şey var: Onları kimin gönderdiği. Son zamanlarda sana kurulan ilk tuzak bu değil. Üstelik üzerinde ayrıntılı tarifin olan bir mektup vardı. Kim bu kadar öfkelendi sana?";
			link.l1.go = "DTSG_Knippel_41";
		break;
		
		case "DTSG_Knippel_41":
			dialog.text = "Şey, ben... Belki Adamsların evinde başka bir şey buluruz, efendim?";
			link.l1 = "Sorudan mı kaçıyorsun? Ama haklısın, zaten burayı iyice aramayı düşünüyordum. Hadi gidelim.";
			link.l1.go = "DTSG_Knippel_42";
		break;
		
		case "DTSG_Knippel_42":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1 = "ExitFromLocation";
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1.location = PChar.location;
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition = "DTSG_PoP_ProverimSunduk";
		break;
		
		case "DTSG_Knippel_50":
			dialog.text = "Vay canına, bu ne kadar çok altın!";
			link.l1 = "Ne yazık ki burada başka bir şey yok. 'Jane' de ortalarda yok. Sence hâlâ hayatta mı?";
			link.l1.go = "DTSG_Knippel_51";
		break;
		
		case "DTSG_Knippel_51":
			dialog.text = "Bilmiyorum, efendim, böyle alçaklar her şeyi yapabilir...";
			link.l1 = "Doğru, ama bana öyle geliyor ki, söylediğinden fazlasını biliyorsun. Seni ilk kez avlamıyorlar. Ve her seferinde üzerlerinde bir yığın para buluyoruz.";
			link.l1.go = "DTSG_Knippel_52";
		break;
		
		case "DTSG_Knippel_52":
			dialog.text = "Emin değilim, Kaptan, ama belki de St. John's'tan bir tefeci olabilir.";
			link.l1 = "Ona nasıl karşı geldin?";
			link.l1.go = "DTSG_Knippel_53";
		break;
		
		case "DTSG_Knippel_53":
			dialog.text = "Pekâlâ... Bir süre önce, tüm diğer borçlarımı kapatmak için ondan borç aldım. Richard ödeyeceğine söz vermişti, ama...";
			link.l1 = "Sence o yapmadı mı?";
			link.l1.go = "DTSG_Knippel_54";
		break;
		
		case "DTSG_Knippel_54":
			dialog.text = "Daha önce inanmazdım ama sana yaptıklarından ve Abi'yle alelacele Karayipler'den ayrılışından sonra... Belki borcu unuttu. Ya da unutmadı ama yine de gitti... Richard tam bir alçak gibi davrandı, efendim. Yine doğru çıkarsa şaşırmam ama yine de hayal kırıklığına uğrarım.";
			link.l1 = "Henüz bu kadar kesin konuşma, Charlie. Öyleyse, St. John's'a gidiyoruz.";
			link.l1.go = "DTSG_Knippel_55";
		break;
		
		case "DTSG_Knippel_55":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			TakeItemFromCharacter(pchar, "letter_1");
			AddQuestRecord("DTSG", "5");
			QuestOpenSeaExit()
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_PiterAdams_20":
			if (CheckAttribute(pchar, "questTemp.DTSG_ZovemMatrosov"))
			{
				dialog.text = "Ah, işte buradasınız efendim - görünüşe bakılırsa herkes erkenden gelmeye karar vermiş. Dış görünüşünüze bakılırsa oldukça keyiflisiniz, yeteneklerinizden bu kadar mı eminsiniz?";
				link.l1 = "Elbette, bu benim ilk düellom olmaktan çok uzak.";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_21";
				ChangeCharacterComplexReputation(pchar, "authority", 1);
			}
			else
			{
				dialog.text = "Geleceğinizden korkmuştum, efendim. Diğerleri zaten burada.";
				link.l1 = "Gerçek bir asilzade sadece kendi ölümüne geç kalabilir.";
				link.l1.go = "DTSG_PiterAdams_NN_21";
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
			}
		break;
		
		case "DTSG_PiterAdams_NN_21":
			dialog.text = "Harika sözler, efendim! İşte rakibimiz Ralph Faggle. Bu da yardımcımız Frederick Stokes.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_22";
		break;
		
		case "DTSG_PiterAdams_NN_22":
			dialog.text = "Buluş...";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_23":
			dialog.text = "Rakibimiz, Ralph Faggle.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_24":
			dialog.text = "Ve bu da bizim ikinci subayımız, Frederick Stokes.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_NN_25":
			dialog.text = "...";
			link.l1 = "Demek bu Ralph? Pek sarhoş bir komşuya benzemiyor.";
			link.l1.go = "DTSG_PiterAdams_NN_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_26":
			dialog.text = "Komşunun kim olabileceğini asla bilemezsin, bunu hiç düşündün mü, Bay de Maure? Heh-heh-heh.";
			link.l1 = "Demek bu bir tuzak... Titremen de geçmiş artık. Ateşli hasta numarası yapmaktan bıktın mı?";
			link.l1.go = "DTSG_PiterAdams_NN_27";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_NN_27":
			dialog.text = "Şu andan sonra bende kalacak tek şey, senin safdilliğine gülerken titremek olur.";
			link.l1 = "Pekâlâ, pekâlâ. Keşke Charlie yanımda olmasaydı diyorum; seninle tek başıma uğraşmak çok daha kolay ve sessiz olurdu...";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_21":
			dialog.text = "Eh, harika!";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_22";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_22":
			dialog.text = "İzin verin, tanıtayım...";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_23":
			dialog.text = "İkinci subayımız Bay Stokes.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_24":
			dialog.text = "Ve bu da Ralph Faggle.";
			link.l1 = "Demek bu Ralph? İtiraf etmeliyim, onu başka türlü hayal etmiştim. Ama neyse, daha beterleriyle de uğraştım.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_25":
			dialog.text = "Hmm, merak ediyorum, saf mısın, hiçbir şey anlamıyor musun? Yoksa kendine fazla mı güveniyorsun?";
			link.l1 = "Ve neyi anlamıyormuşum, Bay Adams? Hadi, şaşırt beni.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_Nastoroje_26":
			dialog.text = "Genelde insanlar böyle durumlarda şaşırır ya da korkar, ama sen farklı birisin anlaşılan. O yüzden o kendinden emin sırıtışını suratından silmek çok daha keyifli olacak, Bay de Maure.";
			link.l1 = "Ne tehditler ama! Aynı tarafta değil miyiz, Peter?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_27";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_27":
			dialog.text = "Bana söyleme, o yaşlı adamla hepimizi alt etmeyi umuyorsun. Sayıca fazlayız, sevgili beyefendi.";
			link.l1 = "Dediğim gibi, anlamayan SENSİN. Charlie biraz homurdandı ama yine de adamlara buraya gelmelerini söylettim, ne olur ne olmaz diye. Meğer boşuna değilmiş. ÇOCUKLAR, BURAYA GELİN!!!";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_28";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_28":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.34, 0.51, 34.93, true, -5.63, -1.20, 57.46);
			DoQuestCheckDelay("DTSG_PoP_Duel_Podkreplenie", 3.0);
			
			int DTSG_PoP_MK;
			if (MOD_SKILL_ENEMY_RATE == 2) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 4) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 6) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 8) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 10) DTSG_PoP_MK = 3;
			
			for (i=1; i<=DTSG_PoP_MK; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_PoP_Matrosy_"+i, "citiz_3"+i, "man", "man", sti(pchar.rank)-5, sti(pchar.nation), -1, false, "quest"));
				GiveItem2Character(sld, "blade_11");
				sld.equip.blade = "blade_11";
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
				LAi_SetHP(sld, 120.0, 120.0);
			}
		break;
		
		case "DTSG_PiterAdams_Nastoroje_29":
			dialog.text = "Ne?..";
			link.l1 = "Şaşırdınız ve korktunuz mu, Bay Adams? Bunu bilmek güzel.";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_BitvaDuel":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("DTSG_PoP_Matrosy_"+i) != -1)
				{
					sld = CharacterFromID("DTSG_PoP_Matrosy_"+i);
					LAi_SetWarriorType(sld);
					LAi_CharacterDisableDialog(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_SetCheckMinHP(sld, 10, true, "KnippelRanen");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_PiterAdams_Duel_Pobeda");
		break;
		
		case "DTSG_Knippel_60":
			dialog.text = "Böyle yalancı alçaklarla işte böyle başa çıkılır. Hâlâ Kraliyet Donanması hakkında yalan söylemeye nasıl cüret ettiklerine inanamıyorum! Zincir gülleyle boğardım onları!..";
			link.l1 = "Artık bazı insanların hiçbir vicdanı olmadığını biliyor olmalısın, Charlie. Ben halledeceğim dedim, gemide kalabilirdin. Bu 'değerli insanlara' yardım edeceğimden emin olmak mı istedin? Ve yine kim haklı çıktı, işin senin sandığın kadar basit olmadığını kim söyledi?";
			link.l1.go = "DTSG_Knippel_61";
		break;
		
		case "DTSG_Knippel_61":
			dialog.text = "Sen, efendim...";
			link.l1 = "Aynen öyle. Ama söyle bana, neden biri seni avlamak istesin? Bu ilk defa olmuyor.";
			link.l1.go = "DTSG_Knippel_62";
		break;
		
		case "DTSG_Knippel_62":
			dialog.text = "Bilmiyorum, Kaptan. Yaşlı Charlie sadece sıradan bir topçu.";
			link.l1 = "Hmm, peki, peki. Tamam, madem şu zavallı düellocuların üstünde işe yarar bir şey yoktu... Hayır, hadi bakalım Adams'ın evinde bir şey bulabilecek miyiz.";
			link.l1.go = "DTSG_Knippel_63";
		break;
		
		case "DTSG_Knippel_63":
			DialogExit();
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			AddDialogExitQuestFunction("DTSG_Knippel_64");
		break;
		
		case "DTSG_Knippel_70":
			dialog.text = "Yani, bu kadın da kaybolmuş... Belki de o 'düellodan' hemen sonra şehirden kaçmaya hazırlanıyorlardı? Hem de aceleyle - burada bu kadar altın varken!";
			link.l1 = "Haklısın, çünkü geride bıraktıkları tek şey altın değil. Bir mektup daha var. O kadar acele etmişler ki yakmayı unutmuşlar. Bak, içeriği hoşuna gidecek.";
			link.l1.go = "DTSG_Knippel_71";
		break;
		
		case "DTSG_Knippel_71":
			TakeItemFromCharacter(pchar, "letter_1");
			dialog.text = "(okur) 'Yaşlı' kısmına itirazım var.";
			link.l1 = "Şimdi mesele bu değil. Bu, sana ikinci kez paralı asker göndermeleri ve onlara para ile bilgi sağlamaları. Üstelik özellikle seni istiyorlar. Söylesene, sen basit bir topçu olarak kimi bu kadar kızdırmış olabilirsin?";
			link.l1.go = "DTSG_Knippel_72";
		break;
		
		case "DTSG_Knippel_72":
			dialog.text = "Bir tahminim var, efendim, sadece bir tane, ve bunun doğru olmasını hiç istemiyorum.";
			link.l1 = "Yani, büyük ihtimalle doğru. Konuş bakalım.";
			link.l1.go = "DTSG_Knippel_73";
		break;
		
		case "DTSG_Knippel_73":
			dialog.text = "Bir zamanlar St. John's'ta çeşitli insanlara borçlarım vardı, ve...";
			link.l1 = "... şimdi de peşinde olduklarını mı düşünüyorsun? Kaçı paralı asker tutacak ve böyle paralar harcayacak durumda?";
			link.l1.go = "DTSG_Knippel_74";
		break;
		
		case "DTSG_Knippel_74":
			dialog.text = "Doğru düşünüyorsunuz, efendim. Sonunda, neredeyse tüm borçlarımı bir tefeciden borç alarak ödedim. Tabii, o bunların hepsini karşılayabilir. Ama...";
			link.l1 = "Ama ne? Borcunu ödeyeceğiz, hepsi bu. Seni endişelendiren ne?";
			link.l1.go = "DTSG_Knippel_75";
		break;
		
		case "DTSG_Knippel_75":
			dialog.text = "Bakın Kaptan, Richard bana borcumu ödeyeceğine söz vermişti.";
			link.l1 = "Sence o yapmadı mı?";
			link.l1.go = "DTSG_Knippel_76";
		break;
		
		case "DTSG_Knippel_76":
			dialog.text = "Artık ne düşüneceğimi bilmiyorum, efendim. Onca zamandır onu örnek bir centilmen olarak tanıdım. Ama sizi bırakıp Abigail’le kaçtıktan sonra… artık hiçbir şeye şaşırmam. O yüzden, doğru olmasını istemem demiştim.";
			link.l1 = "Önce tahminleri kontrol etmek gerek, sonra üzülürsün Charlie. Hadi, St. John's'a tekrar uğrayacaksın.";
			link.l1.go = "DTSG_Knippel_77";
		break;
		
		case "DTSG_Knippel_77":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			AddQuestRecord("DTSG", "6");
			QuestOpenSeaExit()
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_Knippel_PoPDuelTime":
			dialog.text = "Kaptan!!!";
			link.l1 = "Ne oldu Charlie, ne oldu?";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_2";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_2":
			dialog.text = "Ne oldu mu diyorsun?! Sakın düelloyu unuttuğunu söyleme, efendim! Adams çoktan paramparça edilmiş olabilir, sen burada pineklerken!";
			link.l1 = "Pekala!.. Hemen kasabadan çıkacağım.";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_3";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_3":
			DialogExit();
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			DoQuestReloadToLocation("PortPax_ExitTown", "reload", "reload3", "");
		break;
		
		case "DTSG_AntiguaArest":
			dialog.text = "Kaptan Charles de Maure? Yanında Charlie Knippel mi var?";
			link.l1 = "Hayır, bu...";
			link.l1.go = "DTSG_AntiguaArest_2";
		break;
		
		case "DTSG_AntiguaArest_2":
			dialog.text = "İnkâr etmeyin efendim - bu kolonide herkes Charlie'yi tanır.";
			link.l1 = "O zaman neden soruyorsun? Nasıl yardımcı olabilirim?";
			link.l1.go = "DTSG_AntiguaArest_3";
		break;
		
		case "DTSG_AntiguaArest_3":
			dialog.text = "Yapamazsın. Lütfen karşı koyma - Charlie burada aranıyor. Onu gözaltına almamız gerekiyor.";
			link.l1 = "Adamıma hangi suçlamalar yöneltiliyor, öğrenebilir miyim? Borcu yüzünden mi? Onun borcunu ben ödeyebilirim. Hemen şimdi, sizin huzurunuzda, bankere gidelim.";
			link.l1.go = "DTSG_AntiguaArest_4";
		break;
		
		case "DTSG_AntiguaArest_4":
			dialog.text = "Bir borç mu? Bunu ilk defa duyuyorum. Ayrıntıları bilmiyorum ama lütfen işleri zorlaştırma – ben sadece emirleri uyguluyorum.";
			link.l1 = "Ah, harika oldu şimdi...";
			link.l1.go = "DTSG_AntiguaArest_5";
		break;
		
		case "DTSG_AntiguaArest_5":
			StartInstantDialog("Knippel", "DTSG_AntiguaArest_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_AntiguaArest_6":
			dialog.text = "Kaptan...";
			link.l1 = "Charlie, şimdi kaçarsak başımıza konan ödül daha da artacak. Savaşarak çıkamayız da, değil mi? Seni kurtarmaya çalışacağım, ama sakın aptalca bir şey yapma!";
			link.l1.go = "DTSG_AntiguaArest_7";
		break;
		
		case "DTSG_AntiguaArest_7":
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "8");
			pchar.questTemp.DTSG_KnippelDolg = true;
			
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
			sld.location = "None";
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("DTSG_AntiguaSold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
				sld.location = "None";
			}
		break;
		
		case "DTSG_AntiguaStrazhBank":
			dialog.text = "Derhal bu adama bağırmayı ve tehdit etmeyi bırakın, bayım. Silahlarınızı teslim edin ve hemen peşimden gelin!";
			link.l1 = "Kimseyi tehdit etmedim, burada bir yanlışlık var. Bu bir ticaret meselesi, cinayete teşebbüs değil.";
			link.l1.go = "DTSG_AntiguaStrazhBank_2";
		break;
		
		case "DTSG_AntiguaStrazhBank_2":
			dialog.text = "Bana pek öyle gelmiyor. Yasalara hesap vermen gerekecek.";
			link.l1 = "Ya özür dilersem ve gidersem?";
			link.l1.go = "DTSG_AntiguaStrazhBank_3";
		break;
		
		case "DTSG_AntiguaStrazhBank_3":
			dialog.text = "Yani gizlice geri dönüp, yarım bıraktığım işi tamamlayacaksın, öyle mi? Beni aptal mı sanıyorsun?";
			link.l1 = "Eğer bunu barışçıl bir şekilde çözmek istemiyorsan, demek ki gerçekten öylesin. Tanrı biliyor, işin buraya varmasını hiç istemedim...";
			link.l1.go = "DTSG_AntiguaStrazhBank_4";
		break;
		
		case "DTSG_AntiguaStrazhBank_4":
			DialogExit();
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_AntiguaStrazhBank_Ubili");
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki":
			dialog.text = "Onu öldürdün!..";
			link.l1 = "Bunu kendi ellerinizle yaptınız, efendim. Sorularıma düzgünce cevap verebilirdiniz, histerikleşmek yerine. Yemin ederim, bir çığlık daha atarsanız beyninizi dağıtırım.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_V1";
			link.l2 = "Evet, onu ben öldürdüm. Beni buna zorladı. Ama sen onun kadar akılsız değilsin ve onun yaptığını yapmayacaksın, değil mi?";
			link.l2.go = "DTSG_AntiguaUsurer_PosleDraki_V2";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V1":
			dialog.text = "Ne istiyorsun?!";
			link.l1 = "Bir süre önce, Charlie Knippel sizden borç aldı. Onun bir arkadaşı borcunu ödeyeceğine söz verdi ama anlaşılan sözünü tutmadı. Üzerimize paralı asker göndermeyi derhal bırakmanızı istiyorum. Eğer gücüm yeterse, Charlie'nin borcunu hemen ödemeye hazırım.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexLandExpToScill(100, 0, 0);
			AddComplexSeaExpToScill(0, 0, 0, 0, 0, 0, 100);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V2":
			dialog.text = "Ne istiyorsun?!";
			link.l1 = "Bir süre önce, Charlie Knippel senden borç aldı. Arkadaşı borcunu ödeyeceğine söz vermişti ama görünüşe göre ödememiş. Üzerimize paralı askerler göndermeyi derhal bırakmanı talep ediyorum. Eğer gücüm yeterse, Charlie'nin borcunu hemen ödemeye hazırım.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_3":
			dialog.text = "Charlie?! I would never do that to him; he's a good, honest man. Besides, his debt has long been paid off. Mr. Fleetwood, the captain of the Valkyrie, settled it to the last peso.";
			link.l1 = "Gerçekten mi? Kim olduğunu biliyorum. Bunu baştan söylemeliydin. Verdiğim rahatsızlık için üzgünüm, hoşça kal.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_4";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_4":
			dialog.text = "Öyle mi yani?! Beni tehdit ettin! Ve bir adamı öldürdün!..";
			link.l1 = "Ne dediğimi unuttun mu? Bir çığlık daha atarsan, onun yanına gidersin. Hoşça kal.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_5";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_5":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], true);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			npchar.dialog.filename = "Usurer_dialog.c";
			npchar.dialog.currentnode = "First time";
			LAi_SetOwnerType(npchar);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "9");
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1 = "location";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition = "DTSG_AntiguaTrevoga";
		break;
		
		case "DTSG_Killer":
			dialog.text = "Hâlâ buradasın ve henüz asılmamışsın? Peki, Sussex’ten selamlar, Charlie.";
			link.l1 = "Kim olursan ol, sana selamlar.";
			link.l1.go = "DTSG_Killer_2";
			CharacterTurnToLoc(npchar, "goto", "goto9");
		break;
		
		case "DTSG_Killer_2":
			dialog.text = "Ah, Charles de Maure. Zavallı Charlie'yi ziyaret etmen iyi oldu. Bunu bekliyorduk.";
			link.l1 = "Biz kimiz?";
			link.l1.go = "DTSG_Killer_3";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "DTSG_Killer_3":
			dialog.text = "Önemli değil. Bize ciddi zaman ve para kaybettirdiniz, Bay de Maure. Sanırım burada hem Charlie'yle hem de sizinle ilgilenmemde kimsenin bir sakıncası olmaz.";
			link.l1 = "Pekâlâ, madem ikimiz de zaten ölü sayılırız, bize bir iyilik yapıp kimi bu kadar öfkelendirdiğimizi söyler misin? Bir daha yapmayacağımıza söz veriyoruz. Peki, Sussex kim?";
			link.l1.go = "DTSG_Killer_4";
		break;
		
		case "DTSG_Killer_4":
			dialog.text = "Yapamam. Görev çağırıyor ve, senin aksine, ben laf değil iş adamıyım.";
			link.l1 = "Allah aşkına, biri bana neler olup bittiğini anlatacak mı?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Killer_5");
		break;
		
		case "DTSG_KnippelDaySpasen":
			dialog.text = "Vay canına Kaptan, burada tam bir katliam yapmışsınız!";
			link.l1 = "İtirazın mı var? Yoksa darağacını mı tercih edersin? Ya da belki burada sonsuza dek çürümek istersin?";
			link.l1.go = "DTSG_KnippelDaySpasen_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_KnippelDaySpasen_2":
			dialog.text = "Hayır, efendim. Beni kurtardığınız için teşekkür ederim. Açıkçası, gelip beni çıkardığınıza şaşırdım, çünkü beni onlara bu kadar kolay bırakmanı beklemezdim. Ve nöbetçiyi bu kadar kolay alt ettiğine de şaşırdım - o bir Deniz Tilkisiydi. Bir deniz piyadesi.";
			link.l1 = "Sana seni buradan çıkaracağımı söylemiştim, şüphe etmemeliydin. Şimdi tüm garnizon buraya gelmeden bu hücreden çık.";
			link.l1.go = "DTSG_KnippelDaySpasen_3";
		break;
		
		case "DTSG_KnippelDaySpasen_3":
			dialog.text = "Emredersiniz, Kaptan.";
			link.l1 = "...";
			link.l1.go = "DTSG_KnippelDaySpasen_4";
		break;
		
		case "DTSG_KnippelDaySpasen_4":
			DialogExit();
			
			Pchar.GenQuest.Hunter2Pause = true;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("DTSG_TurmaDayPobeda_2", 1.0);
		break;
		
		case "DTSG_KnippelDaySpasen_5":
			dialog.text = "Lanet olsun, komutanım, buna inanmakta zorlanıyorum...";
			link.l1 = "Bu arada, söyle bakalım, seni neyle suçladılar? Ve Sussex kim?";
			link.l1.go = "DTSG_KnippelDaySpasen_6";
		break;
		
		case "DTSG_KnippelDaySpasen_6":
			dialog.text = "Bilmiyorum, efendim. Kimden bahsettiklerini hiç bilmiyorum...";
			link.l1 = "Pekala, bunu sonra öğreniriz. Şimdi buradan çıkmamız lazım.";
			link.l1.go = "DTSG_KnippelDaySpasen_7";
		break;
		
		case "DTSG_KnippelDaySpasen_7":
			DialogExit();
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddPassenger(pchar, npchar, false);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			AddQuestRecord("DTSG", "12");
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_AntiguaNightPirs":
			dialog.text = "Bir sonraki adımınız nedir, efendim? O kan emiciyi gündüz gözüyle pataklamak tehlikeli bir iş.";
			link.l1 = "Bana güzel bir fikir verdin. Neden gündüz vakti onu dövüp aklını başına getirelim ki, bunu şimdi, gecenin karanlığında yapabiliriz?";
			link.l1.go = "DTSG_AntiguaNightPirs_2";
		break;
		
		case "DTSG_AntiguaNightPirs_2":
			dialog.text = "Vay canına, bu harika bir fikir, Kaptan!";
			link.l1 = "Aynen öyle. Söylesene Charlie, bir süre burada yaşadın. Tefecinin nerede oturduğunu biliyor musun?";
			link.l1.go = "DTSG_AntiguaNightPirs_3";
		break;
		
		case "DTSG_AntiguaNightPirs_3":
			dialog.text = "Eskiden bilirdim efendim, ama en son buradayken evini satıyordu. Yeni evinin nerede olduğunu hiç bilmiyorum.";
			link.l1 = "Pekala, bu bir sorun...";
			link.l1.go = "DTSG_AntiguaNightPirs_4";
		break;
		
		case "DTSG_AntiguaNightPirs_4":
			dialog.text = "Eminim bir yolunu bulursun, Kaptan, sonuçta o korkunç Lucas Rodenburg'u alt ettin!";
			link.l2 = "Pekâlâ, hallederim. Ama tefeci nerede oturuyor biliyorsan, çok daha iyi olurdu!";
			link.l2.go = "DTSG_AntiguaIskat_1";
			link.l1 = "Bunu yaptım. Ama sabah akşamdan daha akıllıdır, Charlie. Yolun yorgunluğunu atalım, gündüz gidelim – sonuçta adamı öldürmeye gelmedik.";
			link.l1.go = "DTSG_AntiguaSpat_1";
		break;
		
		case "DTSG_AntiguaSpat_1":
			dialog.text = "Bundan emin misiniz, efendim? Sürpriz avantajımızı kaybedeceğiz.";
			link.l1 = "Eminim ve yorgunum. Ayrıca, sadece konuşmak istiyorum. Gerekirse onu biraz korkuturum.";
			link.l1.go = "DTSG_AntiguaSpat_2";
		break;
		
		case "DTSG_AntiguaSpat_2":
			TavernWaitDate("wait_day");
			DoQuestReloadToLocation("SentJons_tavern_upstairs", "goto", "goto2", "DTSG_AntiguaSpat_3");
		break;
		
		case "DTSG_AntiguaIskat_1":
			dialog.text = "Ne bilmiyorsam, bilmiyorum, üzgünüm, kaptan.";
			link.l1 = "Boşver, hadi onu arayalım.";
			link.l1.go = "DTSG_AntiguaIskat_2";
		break;
		
		case "DTSG_AntiguaIskat_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			AddQuestRecord("DTSG", "13");
			pchar.questTemp.DTSG_NightIskat = true;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.GenQuest.CannotWait = true;
			pchar.questTemp.TimeLock = true;
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood":
			dialog.text = "Aynı şeyi mi düşünüyorsunuz, efendim?";
			link.l1 = "Korkarım öyle, Charlie. Karayipler'de o isimde başka ünlü bir kaptan yok. Ve Richard gerçekten Londra'ya gitti. Yani, bunun tesadüf olması pek mümkün değil.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_2";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_2":
			dialog.text = "Korkunç... Ona karşı ne kadar sert sözler etmiş olsam da, başına böyle bir şey gelsin hiç istemedim! Zavallı Abi!.. Çocuk bekliyordu. Umarım hayattadır...";
			link.l1 = "Gerçekten, kimsenin başına gelsin istemem. Umarım Abi iyidir. Dick'e bunu kimin yapmış olabileceğine dair bir fikrin var mı? Hiç bahsettiği güçlü bir düşmanı oldu mu?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_3";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_3":
			dialog.text = "Şaka yapıyor olmalısınız, Kaptan. Avrupa'da nasıldır bilmem ama burada her Hollandalı Richard'ın ölmesini istiyordu.";
			link.l1 = "Doğru. Belki de burada biri büyük paralar harcadı ve ona Eski Dünya'da suikastçılar gönderdi. Sana yapılan saldırıların arkasında bu önemsiz tefeci değil de, Richard'ın gizemli bir düşmanı olabilir mi?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_4";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_4":
			dialog.text = "Bilmiyorum, efendim. Şu noktada her şey mümkün. Ama bu, hepimiz için işleri zorlaştırır...";
			link.l1 = "Evet, haklısın, ben de bu ihtimali hiç sevmiyorum.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_5";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_5":
			DialogExit();
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "14");
			pchar.questTemp.DTSG_Nastoroje2 = true;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_NightDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator = "houseSp3";
			PChar.quest.DTSG_NightDom.win_condition = "DTSG_NightDom";
		break;
		
		case "DTSG_NightRostovshik":
			dialog.text = "Ne, kim... NE?! Neler oluyor?.. Sen kimsin?!..";
			link.l1 = "Haydi ama. Seni öldürmek isteseydim, uykunda yapardım. O yüzden hayatımızı karmaşıklaştırıp kısaltmayalım. Anladıysan başını salla.";
			link.l1.go = "DTSG_NightRostovshik_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_NightRostovshik_2":
			dialog.text = "Hımm...";
			link.l1 = "Çok iyi. Sakin ol - seni soymaya, kaçırmaya ya da incitmeye gelmedim.";
			link.l1.go = "DTSG_NightRostovshik_3";
		break;
		
		case "DTSG_NightRostovshik_3":
			dialog.text = "O halde... neden buradasın? Neden sabah gelemedin?";
			link.l1 = "Çünkü zengin ve nüfuzlu biri arkadaşımın peşinde. Bunun sen olduğunu düşünmek için sebeplerimiz var, bu yüzden onun gündüz vakti bu sokaklarda dolaşması pek güvenli olmayabilir.";
			link.l1.go = "DTSG_NightRostovshik_4";
		break;
		
		case "DTSG_NightRostovshik_4":
			dialog.text = "Ama gerçekten ne demek istediğinizi anlamıyorum, efendim...";
			link.l1 = "Charlie Knippel. Kasabadaki herkes onu tanır. İyi düşün. Sana borcu var.";
			link.l1.go = "DTSG_NightRostovshik_5";
		break;
		
		case "DTSG_NightRostovshik_5":
			dialog.text = "Bizim yaşlı Charlie mi?? Doğru, ama onun borcu çoktan ödendi, gerçi bizzat kendisi tarafından değil.";
			link.l1 = "Ve bu iyiliksever kimdi?";
			link.l1.go = "DTSG_NightRostovshik_6";
		break;
		
		case "DTSG_NightRostovshik_6":
			dialog.text = "Kaptanı, Lord Richard Fleetwood. Bana inanmıyorsan, kayıtlarımı gösterebilirim.";
			link.l1 = "Fleetwood mu dedin? O zaman sana inanıyorum. Yani, Charlie'nin peşine paralı askerleri sen göndermedin?";
			link.l1.go = "DTSG_NightRostovshik_7";
		break;
		
		case "DTSG_NightRostovshik_7":
			dialog.text = "Tabii ki hayır, neden yapayım ki?? Ve söyle bana, bunun ne anlamı olurdu?";
			link.l1 = "Gerçekten öyle. Geç saatte geldiğim için kusura bakma. İyi geceler.";
			link.l1.go = "DTSG_NightRostovshik_8";
		break;
		
		case "DTSG_NightRostovshik_8":
			DialogExit();
			
			PChar.quest.DTSG_NightDom_3.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.location = "SentJons_houseSP3";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator = "reload1";
			PChar.quest.DTSG_NightDom_3.win_condition = "DTSG_NightDom_3";
			
			LAi_CharacterDisableDialog(npchar);
			Pchar.GenQuest.Hunter2Pause = true;
			AddQuestRecord("DTSG", "15");
		break;
		
		case "DTSG_NightKiller":
			dialog.text = "Ne o Charlie, bu gece eski koruyucunun yanında saklanmayı mı umdun? O orada değil. Ama yakında onunla karşılaşacaksın. Sussex’ten selamlar.";
			link.l1 = "Bunu zaten biliyorduk. Peki Sussex kim? Ve sen kimsin?";
			link.l1.go = "DTSG_NightKiller_2";
		break;
		
		case "DTSG_NightKiller_2":
			dialog.text = "Bu seni ilgilendirmez, Bay de Maure. Ne yazık ki bu işe bizim istediğimizden fazla bulaştın. Başımıza dert oldun.";
			link.l1 = "Kime dert oldum? Lütfen bana söyleme, çok nüfuzlu ve çok öfkeli bir İngiliz'in karısıyla yattığımı.";
			link.l1.go = "DTSG_NightKiller_3";
		break;
		
		case "DTSG_NightKiller_3":
			dialog.text = "Çok komik. Şaka yapacak vakit buldun demek. Hakkında duyduklarım doğruymuş anlaşılan.\nNe istiyoruz? Charlie'nin kellesi yeterli olurdu. Ama bize çıkardığın onca belayı düşününce, bu sefer mesele sadece onunla ilgili değil – burnunu sokmaman gereken işlere karışmaya devam ediyorsun.";
			link.l1 = "Sanırım tutuklandık, öyle mi?";
			link.l1.go = "DTSG_NightKiller_4";
		break;
		
		case "DTSG_NightKiller_4":
			dialog.text = "Tutuklama mı? Hayır, sayın bayım, artık yarım önlemlerin zamanı geçti. Bu bir infaz, Kaptan de Maure.";
			link.l1 = "Kabul. Tek soru şu, kimin.";
			link.l1.go = "DTSG_NightKiller_5";
		break;
		
		case "DTSG_NightKiller_5":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Knippel");
			LAi_SetOfficerType(sld);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DTSG_Killers_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_NightKiller_Pobeda");
		break;
		
		case "DTSG_Knippel_80":
			dialog.text = "Deniz Tilkilerinin işin içinde olacağını düşünmemiştim...";
			link.l1 = "Pekâlâ, her şeyin bir ilki vardır. Söylesene Charlie, Sussex kim?";
			link.l1.go = "DTSG_Knippel_81";
		break;
		
		case "DTSG_Knippel_81":
			dialog.text = "Ben...";
			link.l1 = "Bu işin ne kadar ileri gittiğini göremiyor musun? Ayrıca, anlaşılan aynı durumdayız, Charlie. O yüzden ayrıntıları bilmeye hakkım var.";
			link.l1.go = "DTSG_Knippel_82";
		break;
		
		case "DTSG_Knippel_82":
			dialog.text = "Elbette, Kaptan. Ama burada değil, değil mi? Adadan çıkıp gemide konuşalım.";
			link.l1 = "Haklısın. Peki, hadi acele edelim.";
			link.l1.go = "DTSG_Knippel_83";
		break;
		
		case "DTSG_Knippel_83":
			DialogExit();
			AddQuestRecord("DTSG", "16");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			chrDisableReloadToLocation = false;
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom":
			dialog.text = "Çağırdınız mı, Kaptan?";
			link.l1 = "Evet, Charlie. Konuşmamız lazım. Sanırım ne hakkında olduğunu zaten tahmin ettin.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
			//LAi_LocationDisableOfficersGen("SentJons_town", true);
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_2":
			dialog.text = "Emredersiniz, efendim...";
			link.l1 = "Güzel. O zaman bana söyle, suçlu falan değilken, senin memleketlilerin, üstelik seçkin askerler de dahil, neden seni avlıyor?";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_3";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_3":
			dialog.text = "Gerçekten bilmiyorum, efendim...";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Bu bir şaka değil, Charlie. Peşine düşen kimse, deniz tilkilerine emir verebiliyor. Muhtemelen Richard'ın cinayetinin arkasında da o var. Yani aklında bir şeyler varsa, anlat. Sussex'ten gelen bu selamlar neyin nesi, kim bu?";
			}
			else
			{
				link.l1 = "Bakma başka tarafa, Charlie. Bir şey bildiğini görüyorum. Kaptanın olarak, bana her şeyi anlatmanı emrediyorum. Sussex kim?";
			}
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_4";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_4":
			dialog.text = "Pekala, Kaptan. Sussex bir insan değil. O... bir gemi.";
			link.l1 = "Bir gemiden selam mı? Saçmalık bu.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_5";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_5":
			dialog.text = "Açıklamama izin verin. Oturabilir miyim, efendim? Hikaye uzun ve pek hoş değil.";
			link.l1 = "Elbette, Charlie. Devam et.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_6";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_6":
			DialogExit();
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Knippel"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			SetLaunchFrameFormParam(StringFromKey("Knippel_11", NewStr()), "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
			LaunchFrameForm();
			//DoQuestReloadToLocation("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
		break;
		
		case "DTSG_Kurier":
			dialog.text = "Hey, Charlie, Kaptan Fleetwood'dan geliyorum. Sizi görmek istiyor.";
			link.l1 = "Sağ ol, dostum. Bir şey mi oldu? Genelde her şeyi hemen senin aracılığınla gönderirdi.";
			link.l1.go = "DTSG_Kurier_2";
		break;
		
		case "DTSG_Kurier_2":
			dialog.text = "Bilmiyorum. Bu konuyu doğrudan seninle konuşmak istediğini söylüyor. Senin işin, kendi aranızda halledin.";
			link.l1 = "Ah, bunun hiç iyiye işaret olmadığını hissediyorum...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Kurier_3");
		break;
		
		case "DTSG_Cortny":
			dialog.text = "...";
			link.l1 = "İyi geceler, efendim!";
			link.l1.go = "DTSG_Cortny_2";
		break;
		
		case "DTSG_Cortny_2":
			dialog.text = "İyi geceler. Müsaade edin geçeyim.";
			link.l1 = "Elbette, buyurun, özür dilerim efendim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Cortny_3");
		break;
		
		case "DTSG_Fleetwood":
			dialog.text = "Ah, sensin Charlie. Gel içeri, gel. Kapıyı arkandan kapat.";
			link.l1 = "İyi geceler, Kaptan. Neler oluyor? O adam da kimdi? Kendini beğenmiş bir tavus kuşu...";
			link.l1.go = "DTSG_Fleetwood_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Fleetwood_2":
			dialog.text = "Bunu söyleyemem. Ayrıca konuşmamızı kimsenin duymasına izin veremem. Bunu kimseye anlatma, anlaşıldı mı?";
			link.l1 = "Evet, kaptan. Bir şey mi oldu? Sizi endişeli görüyorum, bu size pek yakışmaz.";
			link.l1.go = "DTSG_Fleetwood_3";
		break;
		
		case "DTSG_Fleetwood_3":
			dialog.text = "Sana öyle geliyor. Sen de pek iyi görünmüyorsun - sonuçta gece oldu. Ama korkarım bu gece için uykun bitti, dostum - acil ve gizli bir görevimiz var.";
			link.l1 = "Ve bu neyi gerektirecek, Kaptan?";
			link.l1.go = "DTSG_Fleetwood_4";
		break;
		
		case "DTSG_Fleetwood_4":
			dialog.text = "Bir hainin ortadan kaldırılması. Kendi içimizden biri. Yakında, Eski Dünya’dan gelen bir diplomatik gemi Dominika kıyılarında belirecek – ‘Sussex’ firkateyni. Resmiyette, Hollandalılarla iyi bir anlaşma yapmak için geliyorlar. Ama gerçekte...";
			link.l1 = "... düşmanlarımıza bilgi mi aktaracaklar, efendim?";
			link.l1.go = "DTSG_Fleetwood_5";
		break;
		
		case "DTSG_Fleetwood_5":
			dialog.text = "Daha da kötüsü. Tamamen onların tarafına geçtiler. Atlantik'i geçtikten sonra yorgun olacaklar ama sonunda, bu iyi bir fırkateyn ve ağır bir gemiyle saldırırsak kesinlikle kaçmaya çalışacaklardır.\nBu yüzden hızlı ve kararlı hareket etmeliyiz. Sadece 'Valkyrie'ye güvenebiliriz - böyle bir görev için uygun tek gemi o.";
			link.l1 = "Yaşlı 'Valkyrie' bir fırkateyni idare edebilecek mi?..";
			link.l1.go = "DTSG_Fleetwood_6";
		break;
		
		case "DTSG_Fleetwood_6":
			dialog.text = "Ha-ha, Charlie, kaptanına güvenmiyor musun? Ayrıca dediğim gibi, onlar bitkin olacak. Ani bir saldırıyla tüm avantaj bizim olur.";
			link.l1 = "Asla yapmam! Ama ne yaptığınızı bildiğinizi umuyorum, efendim...";
			link.l1.go = "DTSG_Fleetwood_7";
		break;
		
		case "DTSG_Fleetwood_7":
			dialog.text = "Bundan eminim. Ve bir şey daha. Bu hain, Parlamento’nun bizzat içinde yüksek bir mevkiye sahip, anladın mı? Her yerde gözü kulağı olabilir – sadece memlekette değil, burada, Karayipler’de de. O yüzden Sussex’i ya da görevimizle ilgili hiçbir detayı şehirde ağzından kaçırma.";
			link.l1 = "Bana söylemenize gerek yoktu, kaptan. Eski Charlie'ye her zaman güvenebilirsiniz.";
			link.l1.go = "DTSG_Fleetwood_8";
		break;
		
		case "DTSG_Fleetwood_8":
			dialog.text = "Biliyorum. Ama bu sefer riskler her zamankinden daha büyük. Eşyalarını topla ve hazırlan - şafakta yelken açıyoruz.";
			link.l1 = "Peki, kaptan. İyi geceler, kaptan.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Fleetwood_9");
		break;
		
		case "DTSG_Knippel_SamSoboi":
			dialog.text = "Richard'ı hiç böyle görmemiştim... Çok endişeliydi, hatta... korkmuş gibiydi?";
			link.l1 = "Ama neden? Bunu benimle bile paylaşmadı. Neyse, önemli değil. O harika bir kaptan, bu yüzden bu fırkateyni ve yorgun tayfasını elbette idare ederiz.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Knippel_SamSoboi_2");
			DeleteAttribute(pchar, "questTemp.lockedMusic");
		break;
		
		case "DTSG_Fleetwood_10":
			dialog.text = "‘Sussex’ ufukta, Charlie, hazırlan.";
			link.l1 = "Her zaman hazırım, Kaptan.";
			link.l1.go = "DTSG_Fleetwood_11";
		break;
		
		case "DTSG_Fleetwood_11":
			dialog.text = "Çok iyi. Sana ve zincirli mermine güveniyorum. Yelkenlerini olabildiğince çabuk parçalamaya çalış, hatta mümkünse bir direk indir. Onları batırmak için tehlikeli bir çatışmaya girmek mantıksız, bu yüzden ben gemiye çıkmaya çalışacağım\nAyrıca, hainin öldüğünden emin olmamız gerek – onları batırsak bile, yine de yaklaşmamız ve kimsenin sağ kalmadığından emin olmamız gerekecek.";
			link.l1 = "Ve bir hain uğruna bu kadar çok yurttaşımızı öldürmek...";
			link.l1.go = "DTSG_Fleetwood_12";
		break;
		
		case "DTSG_Fleetwood_12":
			dialog.text = "Ne yazık ki. Bu durum beni de üzüyor, Charlie. Ama emir, emirdir. En azından bunu eğlence olsun diye yapmıyoruz. O yüzden işi çabucak bitirelim.";
			link.l1 = "Evet, efendim...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Fleetwood_13");
		break;
		
		case "DTSG_Graf_Sheffild_1":
			dialog.text = "Yeter! Kılıcımı teslim etmeye ve isteklerini konuşmaya hazırım. Ama önce, kendini tanıt! Sen kimsin ve bize saldırmaya nasıl cüret edersin?! Bu ihanettir!";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_3":
			dialog.text = "Kaptan Richard Fleetwood. Ve siz de Earl Sheffield olmalısınız? Ve tamamen haklısınız, bu ihanettir.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_5";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_5":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_6":
			dialog.text = "Benim kim olduğumu biliyor musun? Kahretsin! Böyle bir şeyin olacağını biliyordum, her yerde fareler var, bu yüzden sordum, hatta bir savaş gemisi için yalvardım...";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_7";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_7":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_8";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_8":
			dialog.text = "Bu seni kurtarmazdı, sadece kaçınılmazı biraz geciktirirdi, çünkü başka bir yol bulurdum. Ve evet, ihanet derken seninkini kastediyorum, Earl Sheffield.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_9";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_9":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_10":
			dialog.text = "O zaman benim hakkımda hiçbir şey bilmiyorsunuz, efendim! Herkes bilir ki İngiltere'ye benden daha sadık biri yoktur! Bu hatadan pişman olacaksınız, aklınızda bulunsun.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_12";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_12":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_13";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_13":
			dialog.text = "Pişman olacak bir şeyim yok, çünkü Hollandalılara kaçan ben değilim.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_15";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_16":
			dialog.text = "Ne?! Ne saçmalıklar söylüyorsun?! Yanlış yönlendirilmişsin ve deli bir köpek gibi sahte bir iz sürmüşsün\nÖhöm, doğru, Hollanda Batı Hindistan Şirketi ile görüşmelere gidiyorum. Ama bu, İngiltere'mizin çıkarı için, Kaptan. Bu korkunç bir hata, ama hâlâ düzeltebiliriz.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_17";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_17":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_18":
			dialog.text = "Bundan sonrası bana bağlı değil. Size ise hiç değil. Yanlış tarafı seçtiniz, beyler. Hoşça kalın.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_19";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;

		case "DTSG_Graf_Sheffild_19":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Fleetwood");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Graf_Sheffild_20", 0.9);
		break;
		
		case "DTSG_Graf_Sheffild_22":
			dialog.text = "Burada işimiz bitti. Şu şişko adamın çığlıkları hiç bitmeyecek sandım. Ah, şu lordlar yok mu, değil mi Charlie?";
			link.l1 = "Sadece merak ediyorum efendim, ya albay yanıldıysa? Ya da Tanrı korusun, Kont'tan kurtulmak için bize yalan söylediyse?";
			link.l1.go = "DTSG_Graf_Sheffild_23";
		break;
		
		case "DTSG_Graf_Sheffild_23":
			dialog.text = "Dinle beni, dostum. Ve iyi dinle. Hizmetimiz her anlamda çok tehlikeli ve zorlu. Her şey olabilir - acı bir hata, saçma bir tesadüf ya da alçakça bir ihanet\nÜlkeye hizmet etmek sadece toplara gülle doldurmak değildir, Charlie. Güç sahipleri için bu, zor kararlar almak demektir. Biz askerler içinse o kararları uygulamak.";
			link.l1 = "Ama ya bir gün masum kanı dökersek, Kaptan? O zaman bunun vebali bizim ellerimizde, bizim vicdanımızda olur.";
			link.l1.go = "DTSG_Graf_Sheffild_24";
		break;
		
		case "DTSG_Graf_Sheffild_24":
			dialog.text = "O zaman kan onların ellerine de, belki bizden bile fazla, bulaşacak. Bu seni biraz olsun rahatlatır umarım. Önemli olan, niyetimiz temizdi - vatanın düşmanını ortadan kaldırmak.\nŞimdi yardım et bana Charlie, hâlâ bunu Hollandalıların saldırısı gibi göstermemiz gerekiyor.";
			link.l1 = "Evet, efendim...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Graf_Sheffild_25");
		break;
		
		case "DTSG_Knippel_101":
			dialog.text = "Yani, Hollandalıların yapmış gibi görünmesi için sahte deliller bıraktık. Richard'la o günü bir daha hiç konuşmadık.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Şimdi birçok şey anlam kazandı. Sanırım Richard'ın ölümünün arkasında Kont'un bir akrabası ya da destekçisi var. Ama neden seni hedef aldılar? Sonuçta sen sadece bir topçusun ve o kara günde hiçbir karar vermedin.";
				link.l1.go = "DTSG_Knippel_ZS_102";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Experience bonus received");
			}
			else
			{
				link.l1 = "Gerçekten de. Bu iş kötü ve pis kokuyor. Belki birisi öğrendi ve Kont'un intikamını almaya karar verdi. Ama bir topçunun bu kadar masrafa değeceğini sanmıyorum. Para, paralı askerler, Deniz Tilkilerini tutmak... Yok artık Charlie.";
				link.l1.go = "DTSG_Knippel_NS_102";
			}
		break;
		
		case "DTSG_Knippel_ZS_102":
			dialog.text = "Belki de bu kişi Richard'ın eski tayfasından herkesi avlıyor. Ne düşünüyorsunuz, efendim?";
			link.l1 = "Bence Antigua'dan uzak durmalıyız, hem de ne kadar erken olursa o kadar iyi.";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_NS_102":
			dialog.text = "Ben de o soruyu kendime sordum, Kaptan, ama bir cevap bulamadım.";
			link.l1 = "Lanet olsun. Birisi geliyor. Rahatsız edilmememi istemiştim!";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_103":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_103");
		break;
		
		case "DTSG_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Charles!..";
				link.l1 = "Ne oldu, Helen??";
				link.l1.go = "DTSG_Helena_2";
			}
			else
			{
				dialog.text = "Charles, hatırlıyorum, bana kimseyi içeri almamamı ve seni ve Charlie'yi rahatsız etmememi söylemiştin ama...";
				link.l1 = "... kendin gelmeye karar verdin. Peki, tamam, Helen.";
				link.l1.go = "DTSG_Helena_2";
			}
		break;
		
		case "DTSG_Helena_2":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Bir İngiliz savaş gemisi! Bir süre önce fark edildi. Başta önemsemedim, ama şimdi her an bize yetişecek! Böyle hızlı bir gemi görmemiştim.";
				link.l1 = "O halde bana söylediğin için teşekkür ederim. Umarım yaklaşmadan önce hazırlanacak vaktimiz olur. Helen, Charlie, savaş pozisyonlarına!";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
			else
			{
				dialog.text = "... gizli buluşmanıza sonra devam edebilirsiniz. Bir İngiliz savaş gemisi bize doğru geliyor. Bunun önemli olduğunu düşündüm.";
				link.l1 = "Peki, gidip bir bakayım. Teşekkürler, Helen.";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
		break;
		
		case "DTSG_Tichingitu_1":
			dialog.text = "Kaptan, hızlı bir gemi bize doğru geliyor. Hem de çok hızlı. İçimdeki bir his, niyetlerinin kötü olduğunu söylüyor.";
			link.l1 = "Uyarı için sana ve ruhlara teşekkür ederim. Ne olur ne olmaz, savaşa hazırlanın. Ve bu mesajı benim adıma diğerlerine ilet.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_Alonso_1":
			dialog.text = "Affedersiniz, rahatsız ediyorum Kaptan, ama bu acil.";
			link.l1 = "Umarım gerçekten önemli bir şeydir, Alonso. Anlat bakalım.";
			link.l1.go = "DTSG_Alonso_2";
		break;
		
		case "DTSG_Alonso_2":
			dialog.text = "Bir İngiliz gemisi yaklaşıyor. Bu... 'Mirage', Kaptan.";
			link.l1 = "Ne? Emin misin? Yine içtin mi, ha?";
			link.l1.go = "DTSG_Alonso_3";
		break;
		
		case "DTSG_Alonso_3":
			dialog.text = "Eminim, Kaptan - Karayipler'de bunun gibi başka bir gemi yok, bunu siz de biliyorsunuz.";
			link.l1 = "Gerçekten de. Gidip kendim bakacağım - bakalım bu 'Serap' gerçekten var mıymış.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_GotovimsyKBitve":
			DialogExit();
			AddQuestRecord("DTSG", "17");
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Saga\Helena.c";
				sld.Dialog.CurrentNode = "Helena_officer";
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Knippel") != -1 && CheckPassengerInCharacter(pchar, "Knippel"))
			{
				sld = characterFromId("Knippel");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
				sld.Dialog.CurrentNode = "Knippel_officer";
			}
			
			PChar.quest.DTSG_KortniPotopil.win_condition.l1 = "Character_sink";
			PChar.quest.DTSG_KortniPotopil.win_condition.l1.character = "DTSG_Kortni";
			PChar.quest.DTSG_KortniPotopil.win_condition = "DTSG_KortniPotopil";
			
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
		break;
		
		case "DTSG_Kortni":
			dialog.text = "Ah... Ama henüz bitmedi! Brian, işte buradasın! Nerelerdeydin sen?";
			link.l1 = "Bu sadece kaçınılmaz olanı geciktirecek.";
			link.l1.go = "DTSG_Kortni_Pikar";
		break;
		
		case "DTSG_Kortni_Pikar":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "DTSG_KortniRanen");
			LAi_SetImmortal(npchar, false);
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Mrt_Rocur", "citiz_8", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "soldier"));
			sld.name = "Brian";
			sld.lastname = "Tasse";
			GiveItem2Character(sld, "blade_20");
			EquipCharacterByItem(sld, "blade_20");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterByItem(sld, "pistol5");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetHP(sld, 300.0, 300.0);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 10, true, "DTSG_PikarRanen");
			sld.location = "None";
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "DTSG_Kortni_1":
			dialog.text = "Charles de Maure. Şu geldiğin noktaya bak. Yazık. Bu gemide seni hazırlıksız yakalamayı ummuştum.";
			link.l1 = "Kim olduğumu biliyor musun? Demek son zamanlardaki sıkıntılarımızın arkasında sen varsın - rahat yuvasından çıkmaya zorlanmış, başka bir akbaba göndermek yerine bizzat ortaya çıkmak zorunda kalan yüksekten uçan bir kuşa benziyorsun.";
			link.l1.go = "DTSG_Kortni_2";
			
			Island_SetReloadEnableGlobal("Antigua", true);
			bQuestDisableMapEnter = false;
			LAi_LocationDisableOfficersGen("SentJons_town", false);
			DeleteQuestCondition("DTSG_KortniPotopil");
		break;
		
		case "DTSG_Kortni_2":
			dialog.text = "Doğru, ikisinde de haklısın. Sanırım bir soylu, başka bir soyluyu uzaktan tanıyabilir. Albay Thomas Lynch. Görünen o ki, artık birbirimizi yok etmeye çalışmak yerine beyefendi gibi konuşmanın zamanı geldi. Belki de karşılıklı fayda sağlayacak bir anlaşmaya varabiliriz.";
			link.l1 = "Sana hiçbir şey vaat edemem, ama en azından medeni insanlar gibi konuşacağımıza bir asilzade olarak söz veriyorum, Albay.";
			link.l1.go = "DTSG_Kortni_3";
		break;
		
		case "DTSG_Kortni_3":
			dialog.text = "Pekala. Fleetwood'la böyle bir konuşma yapamazdım. Yine de, ona karşı bir koz bulduk ve artık başımıza bela olmayacak. Seninle işler yolunda gitmedi, bu üzücü, ama boşver.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Tüm Karayipler Richard'ın ölümünden bahsediyor. Demek bu senmişsin! Ve bahsettiğin koz da Abigail'di, öyle mi? Bu arada, ona ne oldu?";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Experience bonus received");
			}
			else
			{
				link.l1 = "Bir tehdit değil diyorsun?.. Yani, onu öldürdün mü? Kontun destekçisi misin?";
			}
			link.l1.go = "DTSG_Kortni_4";
		break;
		
		case "DTSG_Kortni_4":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Abigail? Ah, genç Yahudi kadın, nişanlısı. Yine ne kadar dikkatli biri olduğunu kanıtladın. Hayatta ve sağ salim - Fleetwood'un iş birliği karşılığında bunu vaat ettik ve sözümüzü tuttuk.";
				link.l1 = "Gerçekten iyi bir işbirliği oldu, söylemeliyim. Ama neden yaptın bunu? Kontu mu destekliyorsun?";
			}
			else
			{
				dialog.text = "Destekçi mi? Tam tersi. Ama bak, bazı kartlar artık oynanamaz hale gelir, çünkü oyuncuya yük olmaya başlarlar. Ne yazık ki, Richard da onlardan biri oldu.";
				link.l1 = "Anladım. Tüm tanıkları ortadan kaldırıyorsun. Abigail'e ne oldu? Onu da mı öldürdün?";
			}
			link.l1.go = "DTSG_Kortni_5";
		break;
		
		case "DTSG_Kortni_5":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Hiç de öyle değil. Tam tersi. Ama Richard çok şey biliyordu ve Eski Dünya'ya dönerek tehlikeli oldu. Burada kalsaydı, hayatını almak zorunda kalmazdık.";
				link.l1 = "Albay, sizin için çalışan herkesi ortadan mı kaldırıyorsunuz?";
			}
			else
			{
				dialog.text = "Kim? Ah, nişanlısı sanırım. Onu koz olarak kullandılar. Onun hayatı karşılığında kadınınki. Merak etme, iyi, şerefim üzerine yemin ederim.";
				link.l1 = "Yaptıklarınıza bakılırsa, onurun ne olduğunu bildiğinizden şüpheliyim, Albay.";
			}
			link.l1.go = "DTSG_Kortni_6";
		break;
		
		case "DTSG_Kortni_6":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Bu provokasyona cevap vermeyeceğim, efendim.";
				link.l1 = "O halde cevap ver - bu gemiyi nasıl aldın? Yoksa... bu 'Mirage' mi?";
			}
			else
			{
				dialog.text = "Bunu görmezden geleceğim, çünkü bu hakaret, gücü eline alıp işlerin düzenine yön vermek zorunda hiç kalmamış birinden geliyor.";
				link.l1 = "Şeylerden bahsetmişken, 'Mirage'ı nereden buldun? Bu o mu?";
			}
			link.l1.go = "DTSG_Kortni_7";
		break;
		
		case "DTSG_Kortni_7":
			dialog.text = "Tam olarak değil. Muhteşem bir gemi, değil mi? Ne yazık ki sana karşı amacını yerine getiremedi. Bu geminin hikayesini biliyor musun, Kaptan de Maure?";
			link.l1 = "Hayalet gemiyi ve İngiliz tüccarlarının peşine düşmemizi mi kastediyorsun?";
			link.l1.go = "DTSG_Kortni_8";
		break;
		
		case "DTSG_Kortni_8":
			dialog.text = "Şu mu? Hayır, hayır. Ben herkesin bildiği şeylerden bahsetmiyorum. Gözlerden uzak kalanlardan söz ediyorum. Bu ketch'i Johan van Merden ve Lucas Rodenburg tasarladı.\nO tatlı ikili bir dizi oyun kurdu ve sonunda gemi Havana’daki tersaneden suya indirildi. Orijinal planları ele geçirdiğimiz için şanslıydık. Sonunda Mirage’ı tüm görkemiyle yeniden inşa ettik, hatta tasarımındaki bazı kusurları düzelterek onu daha da geliştirdik.";
			link.l1 = "Ne yazık ki, sizin de dediğiniz gibi, bu size pek fayda etmedi, Albay.";
			link.l1.go = "DTSG_Kortni_9";
		break;
		
		case "DTSG_Kortni_9":
			dialog.text = "Gülmek mi istiyorsun? Hiç gerek yok. Kabul ediyorum, hem kaptanlıkta hem dövüşte beni aştın. Ama burada hâlâ üstün olan benim.";
			link.l1 = "Bu bir ölüm numarası mı? Yoksa senin gibilerin alışılmış kendine aşırı güveni mi? Bu sözlerin ardında ne var?";
			link.l1.go = "DTSG_Kortni_10";
		break;
		
		case "DTSG_Kortni_10":
			dialog.text = "Harika bir soru. Görüyorum ki araştırmalarımda anlatılandan fazlasısın; sadece hovarda bir serseri ve düellocu değilsin. Bu buluşmanın her ihtimaline karşı önlem aldım. Hatta senin kılıcınla, kurşununla ya da bir top gülle­siyle öleceğim ihtimale bile. Eğer bugün ölürsem, sen ve Charlie, Fleetwood'a katılmadığınız için pişman olacaksınız.";
			link.l1 = "Daha fazla kelle avcısı mı? Hadi ama. Hoş değildi, sıkıcıydı, ama ölümcül değildi. O zaman da püskürttük, yine püskürtürüz.";
			link.l1.go = "DTSG_Kortni_11";
		break;
		
		case "DTSG_Kortni_11":
			dialog.text = "Hiç şüphem yok. Şimdi yine o umursamaz düellocunun konuştuğunu görüyorum. Peşinde sadece kelle avcıları yok. Deniz Tilkileri'nin tüm gücü ve İngiliz deniz istihbaratı, balıkçı teknesine çarpan fırtına dalgası gibi başına inecek.";
			link.l1 = "Benden ne istiyorsun? Teslim olmamı mı bekliyorsun?";
			link.l1.go = "DTSG_Kortni_12";
		break;
		
		case "DTSG_Kortni_12":
			dialog.text = "Elbette hayır. Bunca zaman seni iyice inceledik. Sana karşılıklı fayda sağlayacak bir anlaşma teklif etmek istiyorum. Reddetmek akıllıca olmaz. Ve iki asilzade olarak, umarım bir anlaşmaya varabiliriz.";
			link.l1 = "O zaman sorumu tekrarlıyorum, Albay, ne istiyorsunuz? Sanırım Charlie'yi?.. Ve bana karşılığında bir şey sunabileceğinizi mi düşünüyorsunuz? Birkaç altın için ihanet etmem.";
			link.l1.go = "DTSG_Kortni_13";
		break;
		
		case "DTSG_Kortni_13":
			dialog.text = "Yine doğru. Mesele sadece birkaç altın sikke değil, dediğin gibi, koca bir dağ - 10.000 doblon. Eğer anlaşmaya varırsak, depozito Port Royal'deki bankacıda seni bekliyor olacak\nAma sunduğum en önemli şey hayatın, Kaptan de Maure. Doğru duydun. Eğer şimdi hepimiz silahlarımızı bırakıp Charlie'yi bize teslim ederseniz, tüm takibi durduracağız\n'Suçlu toplum karşısında' diye bir deyim duydun mu? Senin durumunda, reddedersen, bu 'adam devlete karşı' olacak. Karar ver, Charles. Şimdi ve burada.";
			link.l1 = " Ünvanını ve nüfuzunu kullanarak bir iki ahmağı kolayca korkutabilirsin. Ama ben ahmak değilim. Ve çaresizliği uzaktan hissederim. Defol. Ve seni öldürmediğime şükret – bunu fazlasıyla hak ettin.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
			link.l2 = "Charlie'ye gerçekten ihtiyacınız yok, Albay. Asıl ihtiyacınız olan onun suskunluğu.";
			link.l2.go = "DTSG_Kortni_LT_1";
			link.l3 = "Bunu kendim ve adamlarımın güvenliği için kabul ediyorum, parana tamah ettiğimden değil, bunu bilesin.";
			link.l3.go = "DTSG_Kortni_Sdat";
		break;
		
		case "DTSG_Kortni_PkCh_1":
			dialog.text = "Hayatınızın en kötü kararlarından birini verdiniz, Kaptan de Maure. Size hiç imrenmiyorum. Gerçekten. Suçu yalnızca kendinizde arayın – bir daha kimse size böyle bir teklif sunmayacak. Hele ki ben asla. Elveda.";
			link.l1 = "Bekleyin, Albay.";
			link.l1.go = "DTSG_Kortni_PkCh_2";
		break;
		
		case "DTSG_Kortni_PkCh_2":
			dialog.text = "Ne oldu, fikrini mi değiştirdin? Sonunda söylediklerim etkili oldu mu?";
			link.l1 = "Aynen öyle, tam tersi.";
			link.l1.go = "DTSG_Kortni_PkCh_3";
		break;
		
		case "DTSG_Kortni_PkCh_3":
			dialog.text = "Ne demek istiyorsun? Açıkla kendini.";
			link.l1 = "Sözlerin bana karşı kararlılığımı daha da güçlendirdi. Öyle bakma - seni öldürmeyeceğim. Ve dediğim gibi, gitmene de izin vereceğim. Ama sanırım bir kayığa ihtiyacın olmayacak.";
			link.l1.go = "DTSG_Kortni_PkCh_4";
		break;
		
		case "DTSG_Kortni_PkCh_4":
			dialog.text = "Buna ihtiyacım yok, çünkü bir gemim var.";
			link.l1 = "Haklısın. Ama sadece buna ihtiyacım olmadığı konusunda. Etkili bir adam olabilirsin. Ama ölçün yok. Ve nezaketin de. Senin alışık olduğun şeyi yapacağım – duruma hakim olacağım.";
			link.l1.go = "DTSG_Kortni_PkCh_5";
		break;
		
		case "DTSG_Kortni_PkCh_5":
			dialog.text = "Sen değilsin, Kaptan de Maure. Kendini kandırma.";
			link.l1 = "Tam olarak mı? Belki hayır. Ama sen de öyle değilsin – artık hayatın benim ellerimde, Albay. Sonrasında bana ne olacağı önemli değil – şu anda ne istersem yapabilirim. Ve ben... bu gemiyi alıyorum. Artık özgürsün. Kıyı uzak değil.";
			link.l1.go = "DTSG_Kortni_PkCh_6";
		break;
		
		case "DTSG_Kortni_PkCh_6":
			dialog.text = "Buna cesaret edemezsin. Ama bakışından anlaşılıyor ki... Küçük zaferinin tadını çıkar. Sen...";
			link.l1 = "Evet, evet, hayatımın en kötü kararlarından biriydi. Bunu zaten duydum. Bu gemiden defol. Benim gemimden. Kendin mi atlayacaksın, yoksa seni biz mi denize atalım?";
			link.l1.go = "DTSG_Kortni_PkCh_7";
		break;
		
		case "DTSG_Kortni_PkCh_7":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Kortni_PkCh_7");
		break;
		
		case "DTSG_Kortni_PkCh_8":
			dialog.text = "Onu böyle göreceğim aklıma gelmezdi – aşağılanmış, pencereden atlayıp dört ayak üstünde kıyıya yüzüyor.";
			link.l1 = "Gördün mü? Yeterli mi? Harika. Sıra sende.";
			link.l1.go = "DTSG_Kortni_PkCh_9";
		break;
		
		case "DTSG_Kortni_PkCh_9":
			dialog.text = "What are you saying, sir? We're not enemies; I was just following orders!.. Can I at least ask for a boat? You'll never see me again!";
			link.l1 = "Sen benim yerimde olsaydın ve bana karşı bir savaşı kaybetmiş olsaydın, beni bağışlamazdın. O yüzden seni öldürmediğime şükret. Pencereden dışarı. Şimdi. Belki hamine yetişirsin.";
			link.l1.go = "DTSG_Kortni_PkCh_10";
		break;
		
		case "DTSG_Kortni_PkCh_10":
			dialog.text = "Böyle bir aşağılanmayı yaşamaktansa ölmeyi tercih ederim, monsieur!";
			link.l1 = "Nasıl istersen.";
			link.l1.go = "DTSG_Kortni_PkCh_11";
		break;
		
		case "DTSG_Kortni_PkCh_11":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Kortni_Vyprygnul_3");
		break;
		
		case "DTSG_Kortni_PkCh_12":
			dialog.text = "O, Albaydı değil mi, Kaptan?";
			link.l1 = "Pekala. Şu pencereye bir bak, Charlie, pişman olmayacaksın.";
			link.l1.go = "DTSG_Kortni_PkCh_13";
		break;
		
		case "DTSG_Kortni_PkCh_13":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Kortni_PkCh_13");
		break;
		
		case "DTSG_Kortni_PkCh_14":
			dialog.text = "Albay mı?.. Böyle bir şeyi göreceğim aklıma gelmezdi, efendim. Böylesine bir unvana sahip birini, sıradan bir denizciymiş gibi denize atmaya kim cesaret edebilir! Richard asla böyle bir şey yapmazdı - rütbeye saygı onun en temel özelliğiydi.";
			link.l1 = "Yıllarca süren talimlerle kafasına kazındı bu. O bir asker, askere özgü bir kafa yapısı var. Ben öyle değilim, daha geniş düşünürüm, öyle... kısıtlamalarım yok.";
			link.l1.go = "DTSG_Kortni_PkCh_15";
		break;
		
		case "DTSG_Kortni_PkCh_15":
			dialog.text = "Ve bunu ona yaptığımız için başımız belaya girmez mi?";
			link.l1 = "Heh, Richard'ı suçluyorsun ama onun gibi düşünüyorsun. Direnmeye cesaret ettik, bu yüzden bir süre avlanacağız. Ama er ya da geç, İngiliz donanması bile peşimizi bırakacak. Lynch içinse bu artık kişisel bir mesele olacak. Ama en azından, bir dahaki sefere arkasında devletin gücünü bulamayacak.";
			link.l1.go = "DTSG_Kortni_PkCh_16";
		break;
		
		case "DTSG_Kortni_PkCh_16":
			dialog.text = "Biliyor musunuz, Kaptan, bugünden itibaren size daha da çok saygı duyuyorum. Dick'le Valkyrie'ye binip gitmediğime ve sizinle kalmaya karar verdiğime asla pişman olmayacağım.";
			link.l1 = "Teşekkür ederim, dostum! Hazır ol – fırtına üzerimize geliyor. Ama biliyor musun? İçimde bir his var, yine galip geleceğiz. Hadi, güverteye dönme vakti.";
			link.l1.go = "DTSG_Kortni_PkCh_17";
		break;
		
		case "DTSG_Kortni_PkCh_17":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			DoQuestCheckDelay("DTSG_Kortni_Vyprygnul_7", 3.0);
			Achievment_Set("ach_CL_114");
		break;
		
		case "DTSG_Kortni_LT_1":
			dialog.text = "Bu tam olarak doğru değil, gerçi şahsen, Charlie bundan sonra ağzını tutarsa umurumda olmaz. Ama meslektaşlarım onun cesedini görmek istiyor. Ve onun nasıl göründüğünü biliyorlar\nBu gerçek hayat, Charles, çocuklara anlatılan bir peri masalı ya da dadılarımızın çocukken okuduğu şövalye şiiri değil, ve herkesi memnun edecek bir çözüm göremiyorum.";
			link.l1 = "Ama ben yaparım. Her zaman benzer bir ceset bulabilirsin. Benzer kıyafetler alırsın. Birkaç kişiye rüşvet verirsin. Charlie ile de konuşurum. Ve sana söz veriyorum, bu da teminatım olsun.";
			link.l1.go = "DTSG_Kortni_LT_2";
		break;
		
		case "DTSG_Kortni_LT_2":
			if (sti(pchar.reputation.nobility) > 70)
			{
				Notification_Reputation(true, 71, "low");
				dialog.text = "Bu... büyük bir risk. Ve mesele sadece senin sözüne güvenip güvenemeyeceğim değil. Meslektaşlarım Charlie'ye benzeyen bir ceset gördüklerinde bana inanacaklar mı, asıl mesele bu. Ve ben o riski... öylece almam.";
				link.l1 = "Ne kadar?";
				link.l1.go = "DTSG_Kortni_LT_4";
			}
			else
			{
				Notification_Reputation(false, 71, "low");
				dialog.text = "Senin gibi birinin sözü mü? Şaka yapıyorsun. Soylu doğmak güven için yetmez.";
				link.l1 = "Bunu benzer kökenden ve davranışlardan gelen başka bir adamdan duymak, beni affedin Albay.";
				link.l1.go = "DTSG_Kortni_LT_3";
			}
		break;
		
		case "DTSG_Kortni_LT_3":
			dialog.text = "Elbette, haklısın. Ama bu sefer mesele başkalarının değil, benim güvenim. Ve sen kefil olarak bana uygun değilsin\nSana son kez söylüyorum. Charlie'yi bana ver. Tabii ki, Fleetwood'un akıbetini paylaşmak istemiyorsan.";
			link.l1 = " Ünvanını ve nüfuzunu kullanarak bir iki aptalı kolayca korkutabilirsin. Ama ben aptal değilim. Ve çaresizliği uzaktan hissederim. Defol. Ve şükret ki seni öldürmedim - bunu fazlasıyla hak ediyorsun.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_4":
			dialog.text = "Sonunda, lafı dolandırmadan. Bir milyon peso. Son teklifim.";
			if (sti(pchar.Money) >= 1000000)
			{
				link.l1 = "Sana parayı ödeyeceğim. Ne fakir olduğumu ne de adamlarımın hayatına değer vermediğimi düşünme. Hiçbiri doğru değil. Al şunu.";
				link.l1.go = "DTSG_Kortni_LT_7";
			}
			else
			{
				link.l1 = " İştağın yerinde, gerçi bundan azını beklemezdim. Ama şu anda bende o kadar yok, ve...";
				link.l1.go = "DTSG_Kortni_LT_5";
			}
		break;
		
		case "DTSG_Kortni_LT_5":
			dialog.text = "Gümüş yoksa anlaşma da yok. Merhamet göstereceğimi mi sandın? Aziz gibi mi görünüyorum, efendim?";
			link.l1 = "Ama belki biraz bekleyebilirsin? Senin için nerede ve ne zaman tekrar buluşmak uygun olurdu? Dublonları bir tefeciden ödünç alabilirim.";
			link.l1.go = "DTSG_Kortni_LT_6";
		break;
		
		case "DTSG_Kortni_LT_6":
			dialog.text = "O zaman beni sandığımdan da saf buluyorsun demek\nBen, bir zamanlar gönlünü kaptırdığı adamı sonsuza dek bekleyecek köylü kızı değilim\nParan yok mu? Zaten istemedim ki. Ben sadece Charlie'yi istiyorum. Bunca sıkıntıya rağmen bana hiçbir faydan dokunmadı.";
			link.l1 = " Ünvanını ve nüfuzunu kullanarak bir iki aptalı kolayca korkutabilirsin. Ama ben aptal değilim. Ve çaresizliği uzaktan hissederim. Çık dışarı. Ve şükret ki seni öldürmedim – bunu fazlasıyla hak ediyorsun.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_7":
			dialog.text = "Zavallı Charlie'ye gerçekten bu kadar mı bağlısın? Her halükarda, asaletin saygıyı hak ediyor. Topçunun mezar kadar sessiz olduğundan emin ol. Yoksa ikiniz de orada bulursunuz kendinizi.";
			link.l1 = "Söz veriyorum. Ve sen de sözünü tutup tüm takibi bırakacaksın.";
			link.l1.go = "DTSG_Kortni_LT_8";
			AddMoneyToCharacter(pchar, -1000000);
		break;
		
		case "DTSG_Kortni_LT_8":
			dialog.text = "Ben de söz veriyorum. Ve bir şey daha. Dürüstçe kazandığın halde, gemimi de yanıma alacağım. O özel yapım bir parça, biliyorsun. Hem de çok pahalı.";
			link.l1 = "Ya kazananın hakkı ne olacak? Neyse, şansımı daha fazla zorlamayacağım. Bu sefer.";
			link.l1.go = "DTSG_Kortni_LT_9";
		break;
		
		case "DTSG_Kortni_LT_9":
			DialogExit();
			
			LAi_FadeLong("DTSG_Kortni_Otkup_1", "");
		break;
		
		case "DTSG_Kortni_LT_10":
			dialog.text = "Bunu söylemekten neredeyse üzgünüm, Brian, ama korkarım ki işbirliğimiz burada sona eriyor.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_11";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Mrt_Rocur"));
		break;
		case "DTSG_Kortni_LT_11":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_12";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_12":
			dialog.text = "Ben... özgür müyüm, Albay? Başımda ödülü kaldıracak mısınız ve ben de sanki kanunlara uyan bir adam gibi yeniden başlayabilecek miyim?";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_13";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_KortniClone"));
		break;
		case "DTSG_Kortni_LT_13":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_14":
			dialog.text = "Bence sen de fazlasını gördün - tıpkı merhum Fleetwood gibi. Az önce gözünün önünde rüşvet aldım sayılır.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_15";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Mrt_Rocur"));
		break;
		case "DTSG_Kortni_LT_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_16":
			dialog.text = "Ben... Ben kimseye hiçbir şey söylemeyeceğim, Tanrı’ya yemin ederim!";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_17";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_KortniClone"));
		break;
		case "DTSG_Kortni_LT_17":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_18":
			dialog.text = "Tabii ki, yapmazsın.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_19";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Mrt_Rocur"));
		break;
		case "DTSG_Kortni_LT_19":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_20":
			dialog.text = "Hayır!..";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_21";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_KortniClone"));
		break;
		case "DTSG_Kortni_LT_21":
			DialogExit();
			
			sld = CharacterFromID("DTSG_KortniClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Kortni_Otkup_3", 0.9);
			
			LAi_SetActorType(NPChar);
			LAi_ActorAttack(NPChar, sld, "");
		break;
		
		case "DTSG_Kortni_LT_22":
			dialog.text = "Bana öyle bakma, Charles. Eğer Brian'ın ağzından bir şey kaçırıp kaçırmayacağını sürekli düşünürsem, hiç uyuyamam.";
			link.l1 = " Gördüklerime şaşırmalı mıyım, yoksa şaşırmamalı mıyım, artık bilmiyorum. ";
			link.l1.go = "DTSG_Kortni_LT_23";
		break;
		
		case "DTSG_Kortni_LT_23":
			dialog.text = "Bunu yapmamalısınız. Ben kararlıyım. Sizden tek istediğim, olanlar hakkında kimseye tek kelime etmemek. Ben de benzer bir ceset bulup yüzünü düzgünce ayarlayacağım, parayı iyi değerlendireceğim ve meslektaşlarımı ikna etmeye çalışacağım.";
			link.l1 = "Teşekkür ederim, Albay.";
			link.l1.go = "DTSG_Kortni_LT_24";
		break;
		
		case "DTSG_Kortni_LT_24":
			dialog.text = "Daha teşekkür edecek bir şey yok. Hâlâ bana inanmayabilirler, o zaman da av yeniden başlar. Şimdilik hoşça kal, Kaptan de Maure. Kendi gemimle yola çıkıyorum. İtirazım yok - sana ve Charlie'ye zaten büyük bir iyilik yaptım.";
			link.l1 = "Peki, öyleyse elveda.";
			link.l1.go = "DTSG_Kortni_LT_25";
			
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
		break;
		
		case "DTSG_Kortni_LT_25":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Kortni_LT_25");
		break;
		
		case "DTSG_Kortni_LT_26":
			dialog.text = "Kaptan, kiminle konuştuğunun farkında mısın? Bir albaydı o! Bütün bu karmaşayı o mu başlattı?";
			link.l1 = "Biliyorum, kendini tanıttı. Ve haklısın - oydu.";
			link.l1.go = "DTSG_Kortni_LT_27";
		break;
		
		case "DTSG_Kortni_LT_27":
			dialog.text = "Garip, efendim, çünkü onu bir zamanlar Richard'ın üstü olarak tanırdım. Bu nasıl mümkün olabilir? Ve neden hiçbir şey olmamış gibi ayrılıyor? Zaten ne istemişti?";
			link.l1 = "Aslında bunda garip bir şey yok. Karanlık emirleri yerine getirenler, çoğu zaman hayatlarını düşmanlardan çok üstlerindeki tehlikeye atar. Ve o senin kafanı istiyordu, Charlie.";
			link.l1.go = "DTSG_Kortni_LT_28";
		break;
		
		case "DTSG_Kortni_LT_28":
			dialog.text = "Anlamıyorum, Kaptan. O zaman neden gidiyor? Yenilgiyi mi kabul etti?";
			link.l1 = "Hiç ona benzemez. Ona neredeyse senin kafan kadar ağırlıkta altın vermek zorunda kaldım. Belki biraz daha fazla bile olabilir. Tam olarak bir milyon peso.";
			link.l1.go = "DTSG_Kortni_LT_29";
		break;
		
		case "DTSG_Kortni_LT_29":
			dialog.text = "Ve sen... o kadar büyük bir parayı ona verdin mi? Benim için?..";
			link.l1 = "Yani, sadece senin için değil. Kendim için de. Ve tüm tayfa için de. Ama evet, Charlie, en çok senin için. Onu öldürseydik, sonrasında sonsuza kadar ceza seferleriyle uğraşmak zorunda kalırdık.";
			link.l1.go = "DTSG_Kortni_LT_30";
		break;
		
		case "DTSG_Kortni_LT_30":
			dialog.text = "İnanamıyorum buna, efendim. Sadece... teşekkür ederim. Fleetwood'un sizin yerinizde böyle davranacağını hiç düşünmemiştim.";
			link.l1 = "Ona karşı kaçışından sonra fazla önyargılısın. Richard sadece Abigail’le sakin ve huzurlu bir hayat istiyordu. Onun adına işler yolunda gitmediği için üzgünüm. Üstelik sözünü tuttu ve borcunu ödedi. Heh, ben, Fleetwood – kaptanlar konusunda şansın hep yaver gidiyor, değil mi Charlie?";
			link.l1.go = "DTSG_Kortni_LT_31";
		break;
		
		case "DTSG_Kortni_LT_31":
			dialog.text = "Şaka yapmıyorum, Kaptan. Yani, şimdi her şey bitti mi?";
			link.l1 = "Evet, çok değerli dostum. En azından şimdilik. Kavga bitti - adamlara silahlarını bırakmalarını söyleyebilirsin. Ve yelkenleri hazırlamalarını da iste.";
			link.l1.go = "DTSG_Kortni_LT_32";
		break;
		
		case "DTSG_Kortni_LT_32":
			DialogExit();
			
			InterfaceStates.Buttons.Save.enable = true;
			LAi_SetPlayerType(pchar);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "19");
			CloseQuestHeader("DTSG");
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
			sld = CharacterFromID("Knippel");
			SetCharacterPerk(sld, "Bombardier");
			notification("Bombardier Unlocked", "Knippel");
		break;
		
		case "DTSG_Kortni_Sdat":
			dialog.text = "Neden kabul ettiğin umurumda değil - ister açgözlülükten, ister korkudan, ister adamlarına karşı görevinden olsun. Önemli olan, kabul etmiş olman. Adamımı talimatlarla birlikte Port Royal'e, bankere göndereceğim.";
			link.l1 = "Pekala. Sonunda bittiğine inanamıyorum.";
			link.l1.go = "DTSG_Kortni_Dengi_1";
			link.l2 = "Biliyor musunuz, paranın canı cehenneme. Para her zaman bulunur. Charlie karşılığında sizden başka bir şey istiyorum, Albay.";
			link.l2.go = "DTSG_Kortni_Kech_1";
		break;
		
		case "DTSG_Kortni_Kech_1":
			dialog.text = "Öyle mi? İtiraf etmeliyim, beni şaşırttınız, Kaptan de Maure. Peki, sizin fikrinizce, eski topçunun kel kafasına denk ne olabilir, eğer bir dağ altın size göre değilse?";
			link.l1 = "Bunu kendin söyledin - kusurları düzeltilmiş muhteşem bir gemi. Onu bizzat denemek için sabırsızlanıyorum. Hâlâ planlar sende. Ama Charlie bir tane. Üstelik, beni memnun etmen senin de yararına.";
			link.l1.go = "DTSG_Kortni_Kech_2";
		break;
		
		case "DTSG_Kortni_Kech_2":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				Notification_Reputation(true, 71, "low");
				Notification_Perk(true, "Trustworthy");
				dialog.text = "Sen tam bir pazarlık ustasısın. Bunlardan birini inşa etmenin bize neye mal olduğunu biliyor musun?";
				link.l1 = "(Güvenilir) (Onur) Bunu gayet iyi biliyorum, o yüzden soruyorum. Elin dirseğine kadar çenemde. Bu kurdu vurmayı deneyebilirsin. Ama elini kaybedersin. Hem de sadece onu değil.";
			}
			else
			{
				dialog.text = "Maalesef, bunlardan birini inşa etmek için ayırdığımız altından çok daha fazlası gerekiyor. Ama beni güldürdün, Charles. Hem de iyi anlamda.";
				link.l1 = "Denemeye değerdi.";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
				if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
			}
			link.l1.go = "DTSG_Kortni_Kech_3";
		break;
		
		case "DTSG_Kortni_Kech_3":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				dialog.text = "Ne istediğini biliyor ve hayatındaki hedeflerinin peşinden gidiyorsun, görüyorum\nPekâlâ. Ketch senin. Ama parayı unut - tefeci sana hiçbir şey bilmediğini söyleyecek.";
				link.l1 = "Bu bana uyar.";
				link.l1.go = "DTSG_Kortni_Kech_4";
				pchar.questTemp.DTSG_Kech = true;
			}
			else
			{
				dialog.text = "Kesinlikle. Hayatım fırsatları değerlendirmek ve kendimi tehlikelerden korumakla geçti\nO yüzden Charlie'yi buraya getir, ve dostça yollarımızı ayıralım. Ondan sonra, depozitoyu bile alabilirsin. Ama ben bu gemiyle ayrılıyorum.";
				link.l1 = "O zaman bunu halledelim.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
				pchar.questTemp.DTSG_depozit = true;
			}
		break;
		
		case "DTSG_Kortni_Kech_4":
			dialog.text = "Tam olarak memnun olduğumu söyleyemem. Ama bunu bir an önce bitirmek istiyorum. Şimdi istediğimi ver bana.";
			link.l1 = "Ne 'ne', kim. Ama nasıl istersen.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
		break;
		
		case "DTSG_Kortni_Dengi_1":
			dialog.text = "Ben de yapamıyorum. Artık inanıyorum ki mesele sadece bir adamın kim olduğu değil, kimlerle birlikte olduğudur – yaşlı bir topçuyu yakalamak basit bir iş olmalıydı ama kaptanı yüzünden baş ağrısına döndü, yani senin yüzünden, Charles\nCharlie’yi buraya çağır. Bu karmaşa sonsuza dek bitecek – demir alacağız ve gemilerimiz ayrılacak.";
			link.l1 = "Ayrılmak mı diyorsun?";
			link.l1.go = "DTSG_Kortni_Dengi_2";
		break;
		
		case "DTSG_Kortni_Dengi_2":
			dialog.text = "Şaşırmış gibisin? Kalyonun senin hakkın olan ganimet olduğunu mu sandın? Biz korsan değiliz, Kaptan de Maure. Medeni insanlar bambaşka, çok daha karmaşık kurallarla yaşar. Gemi bende kalıyor.";
			link.l1 = "Pekâlâ o zaman...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
			pchar.questTemp.DTSG_depozit = true;
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_2";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_2":
			dialog.text = "İyi misiniz, efendim? O... albay mı?";
			link.l1 = "Evet, Charlie, albay bu. Tam zamanında geldin – az kalsın seni kendim almaya gidiyordum.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_3";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_3":
			dialog.text = "Beni mi çağırdınız, Kaptan?.. Şimdi mi? Neden bu... adamla bu kadar uzun süredir konuşuyorsunuz? Başınız belada sandım, o yüzden kendim geldim.";
			link.l1 = "Doğru. Zafer kazandık ama hâlâ beladayız. Albayla ben bir çözüm bulmasaydık, bu dertten de kurtulamazdık.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_4";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_4":
			dialog.text = "Onu bizi rahat bırakmaya ikna edebildiniz mi, efendim?";
			link.l1 = "Ne yazık ki, sadece ben. Biz değil. Sen... onunla gideceksin, Charlie.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_5";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_5":
			dialog.text = "Ne?.. Ama neden?.. Kazandık!";
			link.l1 = "Anlamıyor musun? Sürekli kazanmaya devam edemeyiz - senin kafanı alana kadar durmayacaklar.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_6";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_6":
			dialog.text = "Bunu bana yaptığını inanamıyorum, Kaptan. Sen de Dick gibisin. İkiniz de bir zamanlar bana dostum olduğunuzu söylemiştiniz. Ve ikiniz de beni ve size yakın olan herkesi yüzüstü bıraktınız.";
			link.l1 = "Bu bir kaptanın yüküdür, onun sorumluluğu. Belli ki bunu anlayamıyorsun çünkü senin tek yaptığın toplara gülle doldurmaktı.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_7";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_7":
			dialog.text = "Anlamıyor musun?.. Belki de senin gibi bir hain değilimdir? Nereye gitmen gerektiğini biliyor musun?";
			link.l1 = "Cehenneme mi? Belki de haklısın. Hepimiz bunu hak ediyoruz.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_8";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_8":
			dialog.text = "Sokayım, efendim.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_9";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_9":
			DialogExit();
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			sld = CharacterFromID("KnippelClone");
			LAi_SetActorType(sld);
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_10":
			dialog.text = "Çok komik. Neredeyse gülecektim. Duydun mu, Brian?\nBazen şu basit köylülerin konuşmasını duymak insanı ferahlatıyor, hiç de sinir bozucu gelmiyor. Doğru kararı verdin, Charles. Senin için ne kadar zor olduğunu anlıyorum. Ama bil ki, artık ne sen ne de adamlarından biri acı çekecek.";
			link.l1 = "Umarım bu sözünü tutarsın, Albay.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_11";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_11":
			dialog.text = "Ben sözümün eriyim. Abigail’in başına gelenler bunun kanıtı. Brian’a da bak. Fransız bir korsan, ama doğru zamanda doğru tarafı seçti. Ve bize sadık kaldığı sürece kimse ona dokunamaz. Sen de onun gibi doğru yoldasın, Kaptan de Maure.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				link.l1 = "Hareketten söz açılmışken. Buradan bir an önce gitmek istiyorum. Elbette, bana söz verdiğiniz o hızlı gemiyle, Albay.";
			}
			else
			{
				link.l1 = "Ben korsan değilim. Ve henüz İngiliz donanmasına katılmayı düşünmüyorum. Ama vaat edilen ödülü almayı kesinlikle düşünüyorum.";
			}
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_12";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_12":
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				dialog.text = "I won't hide it - it feels like tearing her from my heart. I'll have to spend on a new one, but perhaps it's worth it - too long have I been troubled by the thought that Charlie might spill the beans\nIf you don't talk or commit serious crimes against England, consider that we're no longer enemies. Enjoy the new ship; she's indeed beautiful. Goodbye, Charles. Brian - prepare a boat for us. Charlie - follow me as you have no say in the matter.";
				link.l1 = "Hoşça kalın. Hepiniz.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_13";
			}
			else
			{
				dialog.text = "Yazık, her zaman yetenekli insanlara ihtiyacımız var, milliyetleri ne olursa olsun. Ama elbette, ödülü yine de hak ettin. Port Royal'e gönül rahatlığıyla gidebilirsin - bu ketch ile oraya diğer tüm gemilerden önce varırım.";
				link.l1 = "Umarım öyle olur. Ve umarım Port Royal'da beni silahlı bir muhafız beklemiyordur.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_14";
			}
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_13":
			DialogExit();
			
			AddQuestRecord("DTSG", "20");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_14":
			dialog.text = "Yine mi sözümden şüphe ediyorsun? Yazıklar olsun. Tüm İngiliz donanmasının minnettarlığını kazandın. Bir gün bir şeye ihtiyacın olursa ya da bize katılmak istersen, bana ulaş, Kaptan de Maure.";
			link.l1 = "Bir zamanlar İngiliz istihbaratıyla bağlantı kurmaya ve destek bulmaya çalıştım. Olmadı. O yüzden hoşça kalın, Albay.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_15";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_15":
			DialogExit();
			
			if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
			{
				ChangeCharacterNationReputation(pchar, ENGLAND, 30);
			}
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
			AddQuestRecord("DTSG", "21");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
		break;
		
	}
} 
