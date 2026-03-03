//Jason общий диалог уличных монахов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iTest;
	string sTemp, sTitle;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	iTest = FindColony(NPChar.City);
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> диалог первой встречи
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(npchar, "quest.donation"))//пожертвования
				{
					dialog.text = "İyi günler evladım. Senden bir iyilik rica ediyorum; yoksulların, ruhunun ve Kutsal Ana Kilisesi'nin iyiliği için birkaç gümüş bağışlar mısın?";
					link.l1 = "Pekâlâ Peder, sanırım hepimiz, Mesih ve Kilisesi'nin bize öğrettiği gibi, birbirimize yardım etmeliyiz. Paranın nereye gideceğini bana söyleyebilir misiniz?";
					link.l1.go = "donation";
					link.l2 = "Beni affedin, baba, ama şu anda bir kilise faresinden farksızım.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Monkpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) < 3)//монах-пассажир
				{
					dialog.text = "İyi günler evladım. Senden bir iyilik isteyeceğim. Elbette karşılığını ödeyeceğim.";
					link.l1 = "Sizi dinliyorum, baba. Ne istiyorsunuz?";
					link.l1.go = "passenger";
					link.l2 = "Çok üzgünüm baba, ama gitmem gerekiyor.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.capellan") && !CheckAttribute(pchar, "questTemp.ShipCapellan"))//корабельный капеллан
				{
					dialog.text = "Selam, evladım. Senin bir kaptan olduğunu anlıyorum. O halde sana bir teklifim var.";
					link.l1 = "Dinliyorum, baba.";
					link.l1.go = "capellan";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = PCharRepPhrase(LinkRandPhrase("Selam, evladım. Seni ne üzüyor?","Selam, evladım. Günah çıkarmak istersen papazla konuş.","Selam, oğlum. 'Gençliğinde Yaradan'ı hatırla.' "),LinkRandPhrase("Selam, evladım. Seni ne üzüyor?","Sana iyi günler evladım, Tanrı seni korusun!","Sana iyi günler evladım, Tanrı'nın yüzü üzerine parlasın!"));
				link.l1 = LinkRandPhrase("Sana da, baba. Nasılsın?","İyi günler, baba. Cemaatiniz nasıl?"," Nasılsınız, baba? ");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("Sana bir sorum var, baba.","Bilgiye ihtiyacım var.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10)
				{
					link.l3 = "Baba, gemimde insanlar var. Hem Hristiyanlar hem de vaftiz edilmemiş putperestler. Putperestleri vaftiz etmeni, Hristiyanlara ise komünyon vermeni istiyorum. Sonrasında hepsini Tanrı'nın ve Kilisemizin yüceliği için özgür bırakacağım.";
					link.l3.go = "slaves";
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Babacığım, gemimi kutsamanı ve mürettebatım için ayin düzenlemeni istiyorum. Bunun bedeli ne kadar olur?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Affedersiniz, baba, ama gitmem gerekiyor.","Sizi rahatsız ettiğim için üzgünüm, Peder.","Gemiye dönmem lazım, baba. Elveda!");
				link.l10.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				//--> диалог второй встречи
				dialog.text = LinkRandPhrase("Yine sen misin, evladım? Ne istiyorsun?","Bana başka anlatacak bir şeyin var mı, evladım?","Seni tekrar görmek güzel, evladım.");
				link.l1 = LinkRandPhrase("Sana da, baba. Nasılsın?","İyi günler, Peder. Cemaatiniz nasıl?"," Nasılsınız, baba? ");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("Sana bir sorum var, baba.","Bilgiye ihtiyacım var.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10 && !CheckAttribute(npchar, "quest.slaves"))
					{
						link.l3 = "Baba, gemimde insanlar var. Hem Hristiyan hem de vaftiz edilmemiş putperest kölelerim var. Putperestleri vaftiz etmeni ve Hristiyanlara komünyon vermeni istiyorum. Sonrasında, hepsini Tanrı'nın ve Kilisemizin yüceliği için özgür bırakacağım.";
						link.l3.go = "slaves";
					}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Baba, gemimi kutsamanı ve mürettebatım için ayin düzenlemeni istiyorum. Bunun bedeli ne olur?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Affedersiniz, baba, ama gitmem gerek.","Sizi rahatsız ettiğim için üzgünüm, Peder.","Gemime gitmem gerek, Peder. Elveda!");
				link.l10.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "check":
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) < 3 && !CheckAttribute(npchar, "quest.monkletter") && !CheckAttribute(pchar, "GenQuest.Monkletter") && !CheckAttribute(npchar, "quest.passenger")) //церковная депеша
			{
				pchar.GenQuest.Monkletter.City = FindFriendCityToMC(false);
				pchar.GenQuest.Monkletter.StartCity = npchar.city;//город квестодателя
				dialog.text = "Sana önemli bir işim var, evladım. Bu evrakları   papazına götürmeni istiyorum. "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+". O tarafa mı gidiyorsunuz? Belgeler iki hafta içinde teslim edilmeli...";
				link.l1 = "Kolayca hallederim, baba. O belgeleri bana ver, ben onları teslim ederim "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+".";
				link.l1.go = "Monkletter";
				link.l2 = "Bunu memnuniyetle yapardım baba, ama başka bir yöne yelken açıyorum.";
				link.l2.go = "exit_monkletter";
				npchar.quest.monkletter = "true";
				break;
			}
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) > 5 && sti(pchar.rank < 11) && !CheckAttribute(npchar, "quest.churchbooks") && !CheckAttribute(pchar, "GenQuest.Churchbooks") && !CheckAttribute(npchar, "quest.passenger")) //привезти молитвенники
			{
				pchar.GenQuest.Churchbooks.StartCity = npchar.city;//город квестодателя
				pchar.GenQuest.Churchbooks.Nation = npchar.nation;
				dialog.text = "Oğlum, acil bir konuda bana yardım etmeye razı olur musun? Kilisemizde, ihtiyacı olan herkese verdiğimiz İncil ve dua kitapları tükenmek üzere\nEn yakın kolonilere yelken açabilir misin "+NationNameGenitive(sti(npchar.nation))+", yerel kiliseden birkaç İncil ve dua kitabı alıp buraya getirebilir misin? Ve bunu bir ay içinde yapmaya çalış, elimizde fazla kalmadı.";
				link.l1 = "Kilisenize memnuniyetle yardım ederim. Bu kitapları herhangi bir papazdan alabilir miyim?";
				link.l1.go = "Churchbooks";
				link.l2 = "Bunu memnuniyetle yaparım baba, ama şu anda yapamam.";
				link.l2.go = "exit_churchbooks";
				npchar.quest.churchbooks = "true";
				break;
			}
			
			dialog.text = RandPhraseSimple("Sorun yok, evladım. Nazik sözlerin için teşekkür ederim.","Cemaatimiz iyi, evladım. İlgin için teşekkür ederim.");
			link.l1 = "Öyleyse gitmem gerekiyor, Peder.";
			link.l1.go = "exit";
		break;
		
//-------------------------------------------------пожертвования------------------------------------------------
		case "donation":
			sTemp = DonationType();
			dialog.text = "Elbette, oğlum. "+sTemp+"";
			link.l1 = "Hangi bağış yeterli sayılır?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			dialog.text = "Her şey cüzdanına ve gönlünden ne geçtiğine bağlı, evladım. 'Tanrı, seve seve verenleri sever.' Her türlü bağış için minnettarız.";
			link.l1 = "100 peso";
			link.l1.go = "donation_rate_1";
			link.l2 = "1000 peso";
			link.l2.go = "donation_rate_2";
			link.l3 = "5000 peso";
			link.l3.go = "donation_rate_3";
			link.l4 = "10.000 peso";
			link.l4.go = "donation_rate_4";
		break;
		
		case "donation_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Paralar için teşekkür ederim, evladım! Onlar iyi bir amaç için kullanılacak!";
				link.l1 = "Rica ederim, kutsal baba.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "'Be not deceived, God is not mocked. For whatsoever a man soweth, that shall he also reap. For he that soweth to his flesh shall of the flesh reap corruption; but he that soweth to the Spirit shall of the Spirit reap life everlasting.'";
				link.l1 = "Ha-ha! Vaaz vermeyi bırak, hayır işiyle uğraşmam. Kaybol!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_2":
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Sana teşekkür ediyorum, evladım. Bu miktar gerçekten de cemaatimizin misyonuna büyük katkı sağlayacak. Tanrı seni korusun!";
				link.l1 = "İyi şanslar, baba!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCrewMorale(pchar, 2);
			}
			else
			{
				dialog.text = "Tanrı'nın intikamı seni bekliyor, alçak! Mesih'in kutsal kilisesinin bir hizmetkârıyla alay etmek küfürdür!";
				link.l1 = "Ha-ha! Ben hayır işi yapmam. Defol!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_3":
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Böylesine cömert olacağını hayal bile edemezdim, evladım! Bir sonraki mektubumda seni piskoposumuza mutlaka yazacağım ve her gün senin için dua edeceğiz! Sana hayır duamı gönderiyor ve paranı minnetle kabul ediyorum!";
				link.l1 = "Para, Tanrı'nın amacı için kullanılmadıkça hiçbir şeydir! İyi şanslar, Peder!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCrewMorale(pchar, 3);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			}
			else
			{
				dialog.text = "Tanrı'nın gazabı seni bekliyor, ahlaksız! Mesih'in kutsal kilisesinin bir hizmetkârıyla alay etmek küfürdür!";
				link.l1 = "Ha-ha! Hayırseverlik işim değil. Defol!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_4":
			if (sti(pchar.money) >= 10000)
			{
				AddMoneyToCharacter(pchar, -10000);
				dialog.text = "Ne... Doğru mu duydum? Gerçekten on bin peso bağışlayacak mısınız!? Sizi kutsuyorum ve paranızı minnetle kabul ediyorum. Bir sonraki mektubumda piskoposumuza sizden bahsedeceğim ve her gün sizin için dua edeceğiz! Bu, Kilise için çok büyük bir yardım!";
				link.l1 = " 'Çok verene çok sorulur,' değil mi? Bol şans, kutsal baba.";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 10);
				AddCharacterExpToSkill(pchar, "Leadership", 60);
				AddCrewMorale(pchar, 5);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
				ChangeCrewExp(pchar, "Sailors", 5);
				ChangeCrewExp(pchar, "Cannoners", 5);
				ChangeCrewExp(pchar, "Soldiers", 5);
			}
			else
			{
				dialog.text = "Tanrı'nın gazabı seni bekliyor, alçak! Mesih'in kutsal kilisesinin hizmetkârıyla alay etmek küfürdür!";
				link.l1 = "Ha-ha! Hayırseverlik yapmam. Defol!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterHealth(pchar, -5);
			LAi_CharacterDisableDialog(npchar);
		break;
		
//-------------------------------------------отпустить рабов---------------------------------------------------
		case "slaves":
			dialog.text = "Elbette, evladım. Bu zavallı, perişan insanlara yardım etmek bizim kutsal görevimizdir. İstediğini yapacağım.";
			link.l1 = "Teşekkür ederim, Peder. Vaftiz edilen ve kutsanan her mahkum için sekizli gümüşten on adet bağışlayacağım.";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves_1":
			AddMoneyToCharacter(pchar, -GetSquadronGoods(pchar, GOOD_SLAVES)*10);
			dialog.text = "Gerekli olmasa da, çalınmış ücretinizi memnuniyetle kabul ediyorum. Paranızı cemaatimizdeki çeşitli görevlere harcayacağız. Beni geminize götürebilir misiniz?";
			link.l1 = "Evet, baba. Beni takip et.";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			npchar.quest.slaves = "true";
			DialogExit();
			SetLaunchFrameFormParam("Two hours later"+ NewStr() +"Slaves were freed", "Monk_RemoveSlaves", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
//<-- отпустить рабов

//----------------------------------------------освятить корабль------------------------------------------------
		case "shipshine":
			//поиск старшего класса
			iTemp = 7;
			for (i=0; i<COMPANION_MAX; i++)
			{
				int iIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iIdx >= 0)
				{
					sld = GetCharacter(iIdx);
					if (GetCharacterShipClass(sld) < iTemp) iTemp = GetCharacterShipClass(sld);
				}
			}
			switch (GetCompanionQuantity(pchar))
			{
				case 1: 
					sTemp = "I have only one ship in my squadron and it's "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = 5000*(7-iTemp);
				break;
				case 2:
					sTemp = "I have two ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(1.8*(5000*(7-iTemp)));
				break;
				case 3:
					sTemp = "I have three ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(2.6*(5000*(7-iTemp)));
				break;
				case 4:
					sTemp = "I have four ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(3.4*(5000*(7-iTemp)));
				break;
				case 5:
					sTemp = "I have five ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(4.2*(5000*(7-iTemp)));
				break;
			}
			dialog.text = "Her şey, filonuzdaki toplam gemi sayısına ve onların büyüklüğüne bağlı.";
			link.l1 = ""+sTemp+"";
			link.l1.go = "shipshine_1";
		break;
		
		case "shipshine_1":
			dialog.text = "Sana pahalıya patlar "+FindRussianMoneyString(sti(pchar.GenQuest.Shipshine.Money))+", oğlum.";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Shipshine.Money))
			{
				link.l1 = "Bu parayı ödeyebilirim, baba. Alın paranızı.";
				link.l1.go = "shipshine_2";
			}
			link.l2 = "Maalesef, yanımda o kadar çok param yok.";
			link.l2.go = "shipshine_exit";
		break;
		
		case "shipshine_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Shipshine.Money));
			dialog.text = "Pekâlâ, evladım. Kutsal kapları toplayayım, sonra limana gidelim.";
			link.l1 = "Beni takip et, baba.";
			link.l1.go = "shipshine_3";
		break;
		
		case "shipshine_3":
			DialogExit();
			SetLaunchFrameFormParam("Several hours later"+ NewStr() +"The priest has held mass aboard your ship and blessed it", "Monk_Shipshine", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, GetCompanionQuantity(pchar), 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shipshine_exit":
			DialogExit();
			DeleteAttribute(Pchar, "GenQuest.Shipshine");
		break;
//<-- освятить корабль

//------------------------------------------корабельный капеллан-----------------------------------------------
		case "capellan":
			dialog.text = "Merhaba kaptan, kendimi tanıtmama izin verin. Ben bir rahibim ve savaş gemilerinde papaz olarak epeyce tecrübem var. Son gemimden ayrıldım çünkü kaptanla aramızda bazı... ahlaki anlaşmazlıklar yaşadık. Beni mürettebatınıza almak ister misiniz?";
			link.l1 = "Gemide bir rahip mi var? Söylesene, Peder, bir gemi papazı ne iş yapar?";
			link.l1.go = "capellan_1";
			pchar.questTemp.ShipCapellan = "true";
		break;
		
		case "capellan_1":
			dialog.text = "Neden mi, bu oldukça açık. Sizin ve mürettebatınız için Tanrı'ya dua ederim, her gün ayin yaparım, adamlarınıza kutsama veririm ve savaş öncesi günah çıkartırım. Tanrı'nın sözü, adamlarınızın ellerine ve ruhlarına güç verir. Mürettebatınız düzenli olarak ayin ve günah çıkarma fırsatı bulacak. İnanın bana, lütuf halindeki bir denizci, imansız birinin korkuya kapılacağı durumlarda bile dimdik durur. Kendim için fazla bir şey istemem: memleketimdeki kiliseme elli bin peso tek seferlik bir bağış, kamarada basit bir ranza ve subaylarınızla aynı sofrada yemek. Hepsi bu.";
			if (sti(pchar.money) >= 50000)
			{
				link.l1 = "İlginç... Haklısınız, iyi bir kaptan sadece tayfasının bedenine değil, ruhuna da önem vermeli. Gemimize hoş geldiniz, baba!";
				link.l1.go = "capellan_2";
			}
			link.l2 = "Hayır, baba. Üzgünüm ama hizmetlerinizi karşılayacak durumda değilim.";
			link.l2.go = "capellan_exit";
		break;
		
		case "capellan_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "capellan_2":
			AddMoneyToCharacter(pchar, -50000);
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = "Güvenin için teşekkür ederim, evladım. Paranı akıllıca harcadın. Ama seni uyarıyorum, ben sadece layık kaptanlara hizmet ederim; ister tüccar, ister korsan avcısı olsun, fark etmez. Fakat asla bir korsan gemisinde vaaz vermem!\nEğer bir gün şeytanın siyah bayrağını çekersen, ilk limanda gemini derhal terk ederim.";
			link.l1 = "Bunu dikkate alacağım, baba, ve seni hayal kırıklığına uğratmamaya çalışacağım. Lütfen gemiye çıkıp mürettebata kendini tanıt!";
			link.l1.go = "capellan_3";
		break;
		
		case "capellan_3":
			DialogExit();
			pchar.questTemp.ShipCapellan.id = npchar.id;
			AddDialogExitQuestFunction("Monk_Capellan_DlgExit");
		break;
		
		case "capellan_4":
			dialog.text = "Bir şeye ihtiyacın var mı, evladım?";
			link.l1 = "Hayır, bir şey yok, baba.";
			link.l1.go = "exit";
			link.l2 = "Padre, bir sonraki limanda gemiden inmeni istiyorum. Daha fazla açıklama yapmayacağım.";
			link.l2.go = "capellan_5";
			NextDiag.TempNode = "capellan_4";
		break;
		
		case "capellan_5":
			dialog.text = "Pekâlâ, evladım. Burada sorumlu sensin. Bir sonraki yerleşimde geminden ayrılacağım.";
			link.l1 = "Anlayışınız için teşekkür ederim, baba.";
			link.l1.go = "capellan_6";
		break;
		
		case "capellan_6":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			ShipCapellan_Remove();
		break;
		
		case "capellan_7":
			dialog.text = "Yazıklar olsun kaptan! Sana korsan bayrağını çekersen seni terk edeceğimi söylemiştim! Bir sonraki limanda geminden ayrılıyorum. Senin hemen tövbe edip Kutsal Ana Kilisesi'nin kucağına dönmen için dua edeceğim.";
			link.l1 = "Vay canına...";
			link.l1.go = "exit";
			NextDiag.TempNode = "capellan_7";
		break;
//<-- капеллан
	
//--------------------------------------------монах-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) < 15) SetPassengerParameter("Monkpassenger", false);
			else SetPassengerParameter("Monkpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				dialog.text = "Benim "+GetSexPhrase("oğul","kızım")+",   oraya   gitmem   gerekiyor "+XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+" bu açık "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+", için "+FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty))+". Sana ödeme yapacağım "+FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money))+" bunun için. Ne dersin?";
			}
			else
			{
				dialog.text = "Benim "+GetSexPhrase("oğul","kızım")+", Tanrı'nın yolları gizemlidir ve bu yüzden güvenilir bir kaptan arıyorum. Beni  götürebilir misin? "+XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+",   üzerinde "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+"? Düşmanlarımız asla uyumadığı için bunun ateşli bir Gehenna'ya yolculuk gibi olduğunu anlıyorum. Ve senin İsa Mesih olmadığını da biliyorum, ama ben de bir havari değilim, bu yüzden biraz birikmiş param var. Olur mu "+FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money))+" senin için yeterli olur mu?";
			}
			link.l1 = "Katılıyorum, Peder.";
			link.l1.go = "passenger_1";
			link.l2 = "Üzgünüm baba, ama ben başka bir yöne yelken açıyorum. Sana yardım edemem.";
			link.l2.go = "passenger_exit";
			npchar.quest.passenger = true;
		break;
		
		case "passenger_exit":
			dialog.text = "Tanrı'nın isteği bu, evladım. Başka bir gemiyi bekleyeceğim. Barış seninle olsun!";
			link.l1 = "Elveda, padre.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Monkpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Tanrı seni korusun! Hedefimize vardığımızda ödemenizi alacaksınız.";
			link.l1 = "Gemiye git, baba. Yakında ayrılıyoruz.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Monkpassenger.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "monk");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Monkpassenger.City+"Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Voc")+"."; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Monkpassenger.win_condition.l1 = "location";
			pchar.quest.Monkpassenger.win_condition.l1.location = pchar.GenQuest.Monkpassenger.City+"_town";
			pchar.quest.Monkpassenger.function = "Monkpassenger_complete";
			SetFunctionTimerCondition("Monkpassenger_Over", 0, 0, sti(pchar.GenQuest.Monkpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Monkpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Teşekkür ederim, benim "+GetSexPhrase("oğlum","kızım")+". Sözünü tuttun, şimdi sıra bende. İşte paran, söz verdiğim gibi.";
			link.l1 = "Teşekkür ederim. İyi şanslar, Peder.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Monkpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Monkpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
		break;
//<-- монах-пассажир
		
//---------------------------------------------церковная депеша-------------------------------------------------
		case "exit_monkletter":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter":
			dialog.text = "Al bakalım, oğlum. Bu paketi götür. Unutma, teslim etmek için sadece iki haftan var. Papaz seni bekliyor. Hadi git, Tanrı yanında olsun!";
			link.l1 = "Sana hayal kırıklığı yaşatmayacağım, baba. Elveda.";
			link.l1.go = "Monkletter_1";
		break;
		
		case "Monkletter_1":
			DialogExit();
			GiveItem2Character(pchar, "letter_church");
			ReOpenQuestHeader("Monkletter");
			AddQuestRecord("Monkletter", "1");
			AddQuestUserData("Monkletter", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("Monkletter", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen"));
			AddQuestUserData("Monkletter", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity));
			SetFunctionTimerCondition("Monkletter_Over", 0, 0, 15, false);
			OfficersReaction("good");
		break;
//<-- Церковная депеша
		
//-------------------------------------------доставить молитвенники---------------------------------------------
		case "exit_churchbooks":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;

		case "Churchbooks":
			dialog.text = "Evet. Onları herhangi bir kolonide bulabilirsin "+NationNameGenitive(sti(npchar.nation))+". Bulduğun tüm kitapları kilisedeki papazımıza getir. Tanrı seni korusun!";
			link.l1 = "Teşekkürler! Kitaplarınız yakında elinize ulaşacak.";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			DialogExit();
			ReOpenQuestHeader("Churchbooks");
			AddQuestRecord("Churchbooks", "1");
			AddQuestUserData("Churchbooks", "sNation", NationNameGenitive(sti(pchar.GenQuest.Churchbooks.Nation)));
			AddQuestUserData("Churchbooks", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity));
			SetFunctionTimerCondition("Churchbooks_Over", 0, 0, 30, false);
			pchar.GenQuest.Churchbooks = "go";
			switch (rand(4))
			{
				case 0: pchar.GenQuest.Churchbooks.Item = "amulet_2"; break;
				case 1: pchar.GenQuest.Churchbooks.Item = "amulet_3"; break;
				case 2: pchar.GenQuest.Churchbooks.Item = "amulet_6"; break;
				case 3: pchar.GenQuest.Churchbooks.Item = "amulet_7"; break;
				case 4: pchar.GenQuest.Churchbooks.Item = "amulet_10"; break;
			}
			OfficersReaction("good");
		break;
//<-- доставить молитвенники
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string DonationType()
{
	string sText;
	switch (hrand(9))
	{
		case 0: sText = "I am gathering money for building "+LinkRandPhrase("a chapel","an almshouse","a hospital")+". The local citizens give little in alms so I must ask prosperous men like you." break;
		case 1: sText = "I am gathering donations for our church. Sailors don't usually have much time to visit the house of God, but everyone must do his best in saving his own soul." break;
		case 2: sText = "I am gathering money to buy food and medicines for our poorhouse for the sick, widows, orphans, and infirm. Please donate sir, because there but for the grace of God go all of us." break;
		case 3: sText = "I am gathering money for new sacred vessels, the ones which we brought from Europe are battered with continual use. It's a duty for every Christian to take care of our Church." break;
		case 4: sText = "I am gathering money for our church's renovation, the roof is leaking terribly and the pews have to be repaired too. It's a duty for every Christian to take care of our Church." break;
		case 5: sText = "I am gathering money to pay the good artist who is able to paint the walls of our church and draw scenes from the Bible on them for those of our parish who cannot read. It's a duty for every Christian to take care about his Church." break;
		case 6: sText = "I am gathering money for a new high altar for our church. Our parish is poor and we would like a noble seat for the Blessed Sacrament. I do hope for your help." break;
		case 7: sText = "There are a lot of wounded sailors from pirate raids in our hospital. They need medicines and bandages. Pray help them, for you can really understand sufferings of the common sailors." break;
		case 8: sText = "I am trying to get money for clothes and food for our poorest citizens. The only hope they have is our holy church. Please help them." break;
		case 9: sText = "I am going to go deep in our island for missionary work to bring the light of Christ's Gospel to the lost souls of the pagan Indians. I am gathering funds for this expedition. Please help our good deed!" break;
	}
	return sText;
}
