// Юрген Шмидт - оружейник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iRem;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "Dinle, bayım, neden kavga çıkardın, ha? Atölyemde işin yok, ancak düşmanımızsan burada olabilirsin. Dışarı çık!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! Yaptıklarını duydum. Donald'ın dostu ve bizim müttefikimiz olman iyi oldu. Narvaller dostluğun kıymetini bilir, sana bunu kesinlikle söyleyebilirim.";
					link.l1 = "Umarım öyledir. Şimdi hizmetlerinize güvenebilir miyim?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "Ee? Ne istiyorsun?";
					link.l1 = TimeGreeting()+" . Benim adım "+GetFullName(pchar)+".   Ben de etrafta dolaşıyor, insanlarla tanışıyorum.   Rahatsız mı ediyorum?";
				link.l1.go = "meeting";
				}
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! Yaptıklarını duydum. Donald'ın dostu ve bizim müttefikimiz olman iyi bir şey. Narvaller dostluğa değer verir, sana bunu kesinlikle söyleyebilirim.";
					link.l1 = "Umarım öyledir. Artık hizmetlerinize güvenebilir miyim?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"Yeniden konuşmak mı istiyorsun? Üzgünüm ama ne vaktim var ne de isteğim.";
					link.l1 = "Pekala, seni rahatsız etmeyeceğim.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Kesinlikle! Beni rahatsız ediyorsunuz, bayım. Ben Jurgen Schmidt, Narval klanının silah ve demir ustasıyım. Halkımıza silah sağlıyorum. Ama iyi bir kılıç, anahtar, kilit yapmak ya da bir kule tüfeğinin mekanizmasını onarmak zaman alır. Çokça zaman, sabır ve dikkat ister. Bu yüzden insanların beni rahatsız etmesinden hoşlanmam.";
			link.l1 = "Silah mı yapıyorsun? Senden bir şey sipariş edebilir miyim?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Hayır. Silahları yalnızca Narval klanının üyeleri için yaparım. Bu benim prensibim ve bundan vazgeçmem. O yüzden hiç umutlanma, bayım. Klanımıza katıl ya da en azından müttefikimiz ol, o zaman konuşuruz.";
			link.l1 = "Peki. O zaman seni kendi haline bırakıyorum. Rahatsız ettiğim için üzgünüm!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "friend":
			dialog.text = "Yapabilirsin. Narval'ın dostu benim de dostumdur, o yüzden seni dinliyorum.";
			link.l1 = "Bir kılıç sipariş etmek istiyorum.";
			link.l1.go = "blade";
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l2 = "I've heard that you made a special blade for the late Alan Milrow. I've seen that broadsword; it's a fine weapon. Can I order something like that?";
				link.l2.go = "narval";
			}
			link.l3 = "Henüz bir fikrim yok. Biraz düşüneceğim, sonra geri dönerim!";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "Jurgen":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ha, "+GetFullName(pchar)+"! Demek boğulmamışsın? Ne ilginç! Gerçekten hayatta mısın?";
				link.l1 = "Endişelenme, Jurgen. Hayattayım! Boğulacak değildim...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				NextDiag.TempNode = "Jurgen";
				break;
			}
			dialog.text = "Ah, "+GetFullName(pchar)+"! Ne istiyorsun?";
			if (CheckAttribute(npchar, "quest.narval_blade") && npchar.quest.narval_blade == "ferrum")
			{
				if (GetCharacterItem(pchar, "jewelry11") >= 3)
				{
					link.l4 = "İstediğin gibi üç parça özel demirini getirdim. Bak bakalım, tam istediğin gibi mi?";
					link.l4.go = "narval_7";
				}
				if (CheckCharacterItem(pchar, "meteorite"))
				{
					link.l5 = "Bir bak, Jurgen. Dipte ilginç bir demir külçesi buldum, ama istediğinden çok daha ağır. En az beş pound.";
					link.l5.go = "narval_7_1";
				}
			}
			if (!CheckAttribute(npchar, "quest.blade_done"))
			{
				link.l1 = "Bir kılıç sipariş etmek istiyorum.";
				if (!CheckAttribute(npchar, "quest.blade_rules")) link.l1.go = "blade";
				else link.l1.go = "blade_4";
			}
			if (CheckAttribute(npchar, "quest.blade_payseek"))
			{
				link.l1 = "Sana kılıç için ödeme olarak daha fazla doblon getirdim.";
				link.l1.go = "blade_3";
			}
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive" && npchar.quest.narval_blade == "begin" && pchar.questTemp.LSC != "return") // patch-9
			{
				link.l2 = "Merhum Alan Milrow için özel bir kılıç yaptığını duydum. O pala kılıcı gördüm, gerçekten harika bir silah. Ben de öyle bir şey sipariş edebilir miyim?";
				link.l2.go = "narval";
			}
			if (CheckAttribute(npchar, "blade_date") && GetNpcQuestPastDayParam(npchar, "blade_date") >= 20)
			{
				link.l1 = "Siparişim için geldim. Artık hazır olmalı, değil mi?";
				link.l1.go = "blade_done_2";
			}
			link.l3 = "Hayır, bir şey yok, sadece seni selamlamak istedim.";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		// --> заказ клинков
		case "blade":
			dialog.text = "Pekâlâ. Ama herhangi bir sipariş için bazı özel şartlarım var, bu yüzden önce dikkatlice dinle.";
			link.l1 = "Tamamen seni dinliyorum.";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "You may order only one blade from me, and only once. I don't make specific weapons; you may name only the type - rapier, saber, or broadsword. Think carefully before you make your choice; the final characteristics and quality of the blade will depend on the materials I have at the moment\nNow. It will take twenty days to craft your order. I accept only doubloons. One thousand coins. Payment upfront.";
			link.l1 = "Gerçekten mi! Pahalı...";
			link.l1.go = "blade_2";
		break;
		
		case "blade_2":
			dialog.text = "Pahalıdır. Ama ben mükemmel kılıçlar yaparım, bu yüzden fiyat gayet adil. Karar senin, kimse zorlamıyor.";
			link.l1 = "Anladım, Jurgen. Evet, bir sipariş vermek istiyorum.";
			link.l1.go = "blade_3";
			link.l2 = "Hm. Bir şey sipariş etmeden önce biraz düşünmem lazım. Sonra konuşuruz!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
			npchar.quest.blade_rules = "true";
			npchar.quest.blade_dublon = 1000;
			AddQuestRecord("LSC", "17");
		break;
		
		case "blade_3":
			dialog.text = "Pekâlâ. O zaman ver altınlarını.";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.blade_pay = PCharDublonsTotal();
				link.l1 = "Buyurun, lütfen. Benim var "+FindRussianQtyString(sti(npchar.quest.blade_pay))+".";
				link.l1.go = "blade_pay";
			}
			link.l2 = "Hm. Ne yazık ki şu anda yanımda yok. Ama sana mutlaka getireceğim ve konuşmamıza devam edeceğiz.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "blade_4":
			dialog.text = "Yani bu son kararın mı? Emin misin?";
			link.l1 = "Evet, benim.";
			link.l1.go = "blade_3";
		break;
		
		case "blade_pay": // оплата
			if (sti(npchar.quest.blade_dublon) < sti(npchar.quest.blade_pay)) // полная сумма
			{
				npchar.quest.blade_pay = sti(npchar.quest.blade_dublon);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.blade_dublon)-sti(npchar.quest.blade_pay);
			npchar.quest.blade_dublon = iTemp; // запоминаем остаток
			RemoveDublonsFromPCharTotal(sti(npchar.quest.blade_pay));
			Log_Info("You have given "+sti(npchar.quest.blade_pay)+" doubloons");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "Harika. Yaptığım iş ve malzemeler için bana ödeme yaptınız, şimdi başlayabilirim.";
				link.l1 = "Bir sipariş verebilir miyim?";
				link.l1.go = "blade_done";
			}
			else
			{
				dialog.text = "Pekâlâ. Dublonlarını kabul ediyorum. Bana getirmek zorundasın "+FindRussianQtyString(sti(npchar.quest.blade_dublon))+" daha fazla.";
				link.l1 = "Onları elime geçirdiğimde sana getireceğim.";
				link.l1.go = "exit";
				npchar.quest.blade_payseek = "true";
			}
		break;
		
		case "blade_done":
			DeleteAttribute(npchar, "quest.blade_payseek");
			dialog.text = "Tabii! Hangi türü tercih edersin? İnce kılıçlar, pala kılıçlar mı yoksa geniş kılıçlar mı?";
			link.l1 = "Rapierler. Zarif, hafif silahları severim.";
			link.l1.go = "rapier";
			link.l2 = "Kılıçlar. Bana sorarsan, en iyisi onlar.";
			link.l2.go = "sabre";
			link.l3 = "Kesinlikle pala kılıçlar! Kes ve parçala!";
			link.l3.go = "palash";
		break;
		
		case "rapier":
			npchar.quest.blade_done = SelectJurgenBladeDone("rapier");
			dialog.text = "Dediğiniz gibi. Siparişinizi almak için yirmi gün sonra gelin, daha erken değil.";
			link.l1 = "Teşekkür ederim! Yirmi gün sonra görüşürüz. Hoşça kal, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "sabre":
			npchar.quest.blade_done = SelectJurgenBladeDone("sabre");
			dialog.text = "Dediğiniz gibi. Siparişinizi yirmi gün sonra almaya gelin, daha erken değil.";
			link.l1 = "Teşekkür ederim! Yirmi gün sonra görüşürüz. Hoşça kal, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "palash":
			npchar.quest.blade_done = SelectJurgenBladeDone("palash");
			dialog.text = "Dediğiniz gibi. Siparişinizi yirmi gün sonra, daha erken değil, almaya gelin.";
			link.l1 = "Teşekkürler! Yirmi gün sonra görüşürüz. Hoşça kal, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "blade_done_1":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "blade_date");
			NextDiag.CurrentNode = "Jurgen";
			AddQuestRecord("LSC", "18");
		break;
		
		case "blade_done_2":
			dialog.text = "Evet. Kılıcınız hazır. Lütfen alın ve kullanın. Ona dokunduğunuz anda değerini anlayacaksınız.";
			link.l1 = "Teşekkürler, Jurgen.";
			link.l1.go = "blade_done_3";
		break;
		
		case "blade_done_3":
			DialogExit();
			NextDiag.CurrentNode = "Jurgen";
			GiveItem2Character(pchar, npchar.quest.blade_done);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "blade_date");
		break;
		
		// заказ палаша Нарвал для Мэри
		case "narval":
			dialog.text = "Ne yazık ki, dostum, iki sebepten dolayı reddetmek zorundayım. Birincisi, böyle bir pala sadece Narval klanından ve özel biri için yaparım. İkincisi ise, bunun için gerekli malzemeler elimde yok.";
			link.l1 = "Ve bu özel demir dediğin nedir? Duyduğuma göre onu denizin dibinden çıkarmışlar...";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "Kesinlikle. Bu metalin parçaları sığlığımızın her yerine dağılmış durumda. Nasıl geldiklerini bilmiyorum. Ama bu demir eşsizdir, asla paslanmaz ve ondan yapılan bıçaklar hiç körelmez. Yani eğer demiri bulmayı başarırsan, meseleyi çözebiliriz. Ama hâlâ bir sorun var, sen bir Narval değilsin...";
			link.l1 = "Hm. Gerçekten önemli mi?";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "Evet. Bunu bir kaprisim olarak görebilirsin, ama böyle bir pala sadece Narval için yaparım.";
			link.l1 = "Pekâlâ... Tamam, bunu kabul ediyorum. Ama bir fikrim var. Bu kılıcı Narval klanından birine sipariş edebilir miyim?";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "Hm. Sanırım getirdiğin demirle yapabilirim. Bu, prensiplerime aykırı olmaz... Ve bu pala kılıcı kimin için yapmamı istiyorsun?";
			link.l1 = "Kızıl Mary için. O, Narval klanından ve böyle mükemmel bir silahı hak ediyor.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "Ha! Bunu kendim de anlayabilirdim. Yaşlandım artık... Neyse, katılıyorum. Eminim Mary böyle bir hediyeye gerçekten çok sevinecek... Demiri getir, ben de pala kılıcı yapayım. Kılıcın çeliği için... ah, neyse, bunu bedavaya yapacağım. Bu hediye sadece senden değil, ikimizden de olacak.";
			link.l1 = "Teşekkürler! Ne kadar demire ihtiyacın var?";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "En altta bulduğumuz o parçaların hepsi aynıydı - her biri birer pound. Onlardan üç tane daha lazım bana.";
			link.l1 = "Pekala. Onları bulmaya çalışacağım. Sonra tekrar konuşuruz.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			DialogExit();
			npchar.quest.narval_blade = "ferrum";
			NextDiag.CurrentNode = "Jurgen";
			// кладем гигантский кусок метеорита на дно
			sld = ItemsFromID("meteorite");
			sld.shown = true;
			sld.startLocation = "underwater";
			sld.startLocator = "item"+(rand(7)+1);
			Log_TestInfo("Meteorite in the locator " + sld.startLocator);
			pchar.quest.LSC_narval_ferrum.win_condition.l1 = "item";
			pchar.quest.LSC_narval_ferrum.win_condition.l1.item = "meteorite";
			pchar.quest.LSC_narval_ferrum.function = "LSC_NarvalFerrum";
			AddQuestRecord("LSC", "19");
		break;
		
		case "narval_7":
			RemoveItems(pchar, "jewelry11", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "Bir bakayım... Evet, bu o! Böyle küçük parçaları dipte bulmak zor muydu?";
			link.l1 = "Ne diyebilirim ki... Mary böyle bir zahmete değer, değil mi?";
			link.l1.go = "narval_8";
			pchar.quest.LSC_narval_ferrum.over = "yes"; //снять прерывание
		break;
		
		case "narval_7_1":
			RemoveItems(pchar, "meteorite", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Bir bakayım... Bu da ne! Evet, bu dip demiri, ama bu kadar büyük parçalarını daha önce hiç görmemiştim. Bu, pala yapmak için yeterli olacak. Bulması zor muydu?";
			link.l1 = "Ne diyebilirim ki... Mary böyle zahmete değer, değil mi?";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			dialog.text = "Senden her geçen gün daha çok hoşlanıyorum, "+pchar.name+"... Pekâlâ o zaman. Şimdi güzel Amazonumuz adına çalışma sırası bende. Palayı yapmak iki gün sürecek, diğer siparişleri bir kenara bırakacağım\nMary'yi ertesi gün bana getir. Ona söyleme, bu bir sürpriz. Bir çocuk gibi sevinecek.";
			link.l1 = "Pekala, Jurgen. Anlaştık! İki gün sonra görüşürüz!";
			link.l1.go = "narval_9";
		break;
		
		case "narval_9":
			DialogExit();
			npchar.quest.narval_blade = "work";
			NextDiag.CurrentNode = "narval_10";
			SetFunctionTimerCondition("LSC_NarvalBladeForMary", 0, 0, 2, false); // таймер
			AddQuestRecord("LSC", "21");
		break;
		
		case "narval_10":
			dialog.text = ""+pchar.name+", beni rahatsız etme. Kılıcı zamanında bitirmemi istiyorsun, değil mi?";
			link.l1 = "Evet, tabii. Gidiyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_10";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Orada ne yapıyorsun, ha? Hırsız!","Şuna bak! Ben dalıp gitmişken, sen de sandığımı karıştırmaya kalktın!","Sandıklarımı mı kurcalamaya karar verdin? Bunu yanına bırakmam!");
			link.l1 = "Lanet olsun!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Dinle, silahını yerine koysan iyi olur. Bu beni tedirgin ediyor.","Biliyor musun, burada elinde bıçakla dolaşmana izin verilmez. Onu yerine koy.","Bak, elinde kılıçla ortalıkta dolaşan bir ortaçağ şövalyesi gibi davranma. Onu yerine koy, sana yakışmıyor...");
			link.l1 = LinkRandPhrase("Peki.","Pekâlâ.","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dinle, ben bu şehrin bir vatandaşıyım ve senden kılıcını indirmeni rica ediyorum.","Dinle, ben bu şehrin bir vatandaşıyım ve senden kılıcını indirmeni rica ediyorum.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dikkatli ol, dostum, elinde silahla dolaşıyorsun. Beni tedirgin edebilirsin...","Silahları çekilmiş adamların önümde yürümesinden hoşlanmıyorum. Bu beni korkutuyor...");
				link.l1 = RandPhraseSimple("Anladım.","Bunu alıp götürüyorum.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string SelectJurgenBladeDone(string _sType)
{
	string sBlade;
	switch (_sType)
	{
		case "rapier":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_18"; 
			else sBlade = "q_blade_16";
		break;
		
		case "sabre":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_19"; 
			else sBlade = "q_blade_10";
		break;
		
		case "palash":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_21"; 
			else sBlade = "q_blade_13";
		break;
	}
	return sBlade;
}
