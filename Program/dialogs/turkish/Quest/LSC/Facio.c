// посредник-дипломат кланов Джузеппе Фацио
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Merhaba, merhaba... Yeni misin burada? Yüzünü hatırlamıyorum. Kendimi tanıtmama izin ver - Ben Giuseppe Fazio, bu küçük adada sorunları çözme konusunda uzmanım.";
				link.l1 = TimeGreeting()+" . Benim adım "+GetFullName(pchar)+" . Haklısınız, ben buraya yeniyim. Merakımı mazur görün – ama ne tür sorunlarla ilgileniyorsunuz?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, yine sen, sevgili "+pchar.name+"! Ne rüzgar attı seni bu mütevazı yuvama?";
				if (CheckAttribute(pchar, "GenQuest.NarvalConflict") || CheckAttribute(pchar, "GenQuest.RivadosConflict") || CheckAttribute(pchar, "GenQuest.SharkConflict"))
				{
					link.l10 = "Fazio, bir klanla ciddi bir sorunum var. Bu meseleyi çözmem gerekiyor.";
					link.l10.go = "conflict";
				}
				// --> квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_3")
				{
					link.l4 = "Giuseppe, Adolf Barbier adında bir adamı arıyorum. Son zamanlarda onunla meyhanede içki içtiğini duydum...";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && pchar.questTemp.LSC.Drink == "begin")
				{
					link.l5 = "Giuseppe, senin içkiye tamamen dayanıklı olduğunu söylüyorlar. Ne kadar içersen iç, yine de ayakta kalıyorsun.";
					link.l5.go = "drink";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && PCharDublonsTotal() >= 100 && pchar.questTemp.LSC.Drink == "wait")
				{
					link.l5 = "Oyununu oynamaya hazırım. İşte ortaya koyduğum pay.";
					link.l5.go = "drink_4";
				}
				// <-- квестовые ветки
				if (CheckAttribute(npchar, "quest.parol"))
				{
					link.l1 = "Kabilelerin bölgelerine girmek için şu anki şifrelerini öğrenmek istiyorum.";
					link.l1.go = "parol_choice";
				}
				link.l2 = LinkRandPhrase("Söyleyecek ilginç bir şeyin var mı?","Adada yeni bir şey oldu mu?","Bana son dedikoduları anlatır mısın?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Özel bir şey yok, Giuseppe. Sadece seni görmek istedim.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Her türlüsü, canım, her türlüsü. Mesela, amiral ile klanlar arasındaki işleri yumuşatırım. Zaten biliyor olabilirsin, Rivados, Narvaller ve amiral birbirlerinin ezeli düşmanıdır. İşler zorlaştığında arabulucu olarak devreye girerim.\nAyrıca, amiral klanlara erzak sattığında sık sık tarafsız biri gibi davranırım. Ama bu işimin sadece küçük bir parçası. Yani eğer Rivados ya da Narvaller ile başın derde girerse - yardımıma başvurmaktan çekinme, neler yapabileceğimize bakarız.";
			link.l1 = "Pekâlâ. Bunu düşüneceğim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// пароли
		case "parol_choice":
			dialog.text = "Hangi klan?";
			link.l1 = "Narvaller.";
			link.l1.go = "parol_nrv";
			link.l2 = "Rivados.";
			link.l2.go = "parol_rvd";
		break;
		
		case "parol_nrv":
			dialog.text = "Donald Greenspen'i görmek istiyorsun, değil mi?";
			link.l1 = "Doğru. Peki, parolayı biliyor musun?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Narwals";
			sTotalTemp = sNrvParol;
		break;
		
		case "parol_rvd":
			dialog.text = "Siyah Eddie'yi görmek istiyorsun, değil mi?";
			link.l1 = "Öyle sayılır. Peki, parolayı biliyor musun?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Rivados";
			sTotalTemp = sRvdParol;
		break;
		
		case "parol":
			if (!CheckAttribute(npchar, "quest.parolrules"))
			{
				dialog.text = "Tabii! Ama önce sana bazı detaylar vereyim. Şifreler tek bir kelimeden oluşur ve her hafta değişir: ayın yedinci, on dördüncü, yirmi birinci ve yirmi sekizinci günlerinde.\nBu yüzden hata yapmamak için bugünün tarihine dikkat et. Son olarak, anlamışsındır, bu bir hayır işi değil. Bir şifre için elli dublon isterim. Unutma, sadece dublon geçerli.";
				link.l1 = "Elli doblon mu? Bu çok büyük bir meblağ!";
				link.l1.go = "parol_1";
			}
			else
			{
				dialog.text = "Tabii, evlat. Fiyatı biliyorsun. Elli dublonun var mı?";
				if (PCharDublonsTotal() >= 50)
				{
					link.l1 = "Evet. Al paralarını.";
					link.l1.go = "parol_pay";
				}
				link.l2 = "Maalesef, bilmiyorum. Belki sonra...";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "parol_1":
			dialog.text = "Pekâlâ, pekâlâ, evlat, sakin ol. Açgözlü olma, bana güven: Bilgimin gerçek değerini iyi bilirim. Gemilerin arasında öylece dolaşacak değilsin "+pchar.questTemp.LSC.parol+" değil mi? Doğru. Yani biraz altın kaybetmeye hazır olmalısın... Peki, elli dublon ödemeye hazır mısın?";
			if (PCharDublonsTotal() >= 50)
			{
				link.l1 = "Evet. Al paralarını.";
				link.l1.go = "parol_pay";
			}
			link.l2 = "Maalesef, o kadar param yok. Belki sonra...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
			npchar.quest.parolrules = "true";
		break;
		
		case "parol_pay":
			RemoveDublonsFromPCharTotal(50);
			dialog.text = "Harika! Seninle iş yapmak bir zevk. Şu anki parola "+pchar.questTemp.LSC.parol+" is: '"+sTotalTemp+"'. Bunu iyi hatırla ve sakın hata yapma, yoksa hayatın için bir kuruş bile vermem.";
			link.l1 = "Biliyorum, biliyorum... Teşekkürler!";
			link.l1.go = "exit";
			AddQuestRecord("LSC", "parol");
			AddQuestUserData("LSC", "sText", pchar.questTemp.LSC.parol);
			AddQuestUserData("LSC", "sParol", sTotalTemp);
			if (pchar.questTemp.LSC.parol == "Rivados") pchar.questTemp.LSC.RParol_bye = "true";
			else pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "adolf":
			dialog.text = "Ah, ama tabii ki, benim eski dostum Adolfo! Evet, onunla konuştum. Bak canım, paramı geri aldığım için çok sevindim, bir daha asla göremem sandığım parayı! Adolfo, harika tüfeğini teminat göstererek benden yüklü bir miktar borç aldı ve paramı geri ödemekte zorlandı\nArtık umudumu tamamen kaybetmiş, o stutzen'i sevgili Axel Yost'umuza satmaya hazırlanıyordum. Ama birdenbire, sevgili Adolfo altınlarımı bana getirdi! Meğer sadece stutzen'ini geri almak için değil, aynı zamanda 'Santa Florentina'nın başındaki Sessile Gallard'ın kamarasını satın almak için de yeterince para toplamış!\nTabii, yarı su basmış bir ambar yerine burada yaşamak çok daha iyi\nYani, Adolfo tüfeğini geri aldı, yeni bir evi var ve ben de paramı aldım. O bana içki ısmarlarken, onunla bir kadeh içmeyi neden reddedeyim ki?";
			link.l1 = "Ah, tabii! İçmek için bolca sebebin vardı. Hem de bedavaya... Teşekkürler Giuseppe, bana çok yardımcı oldun. Artık Adolf'u nerede bulacağımı biliyorum.";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Her zaman zevkle, canım. Ama Adolfo'yu akşam olmadan kamarasında arama, çok meşgul, bir iş peşinde oradan oraya koşturuyor... Evet, bir de beni daha sık ziyaret et, sohbet edelim!";
			link.l1 = "Kendi kamarama sahip olduğumda seni davet edeceğim... Hoşça kal, bol şanslar!";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			DialogExit();
			LSC_CreateAdolfClone(); // заменяем Адольфа клоном
			pchar.questTemp.Saga.SharkHunt = "search_mush_4"; //флаг на Адольфа в каюте
			AddQuestRecord("SharkHunt", "14");
		break;
		
		case "whiskey":
			switch (sti(npchar.quest.poisonnode))
			{
				case 1: // у себя
					dialog.text = "Ha? Neden yangın varmış gibi evime dalıyorsun? Sen kendini kim sanıyorsun??";
					link.l1 = "Senin adaletin... zehirci!";
					link.l1.go = "whiskey_1";
				break;
				
				case 2: // на Эве
					dialog.text = "Beni bağışlayın! Yemin ederim, beni zorladılar! Tabancayı kafama dayadılar...";
					link.l1 = "Kapa çeneni. Bunu biliyorum. Son piç nerede? Marcello Cyclops nerede?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
				
				case 3: // у Акулы
					dialog.text = "Yemin ederim, beni zorladılar! Amiral'e her şeyi zaten anlattım! Onlara karşı koyamadım, yoksa...";
					link.l1 = "Kapa çeneni. Bunu biliyorum. Son o... nerede? Marcello Cyclops nerede?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
			}
		break;
		
		case "whiskey_1":
			dialog.text = "Ne... ne dediniz?";
			link.l1 = "Her şeyi biliyorum, alçak. Chad Kapper'la iş birliği yaptın. Amiral için zehirli rom fıçısı getirdin. Şimdi dua et, zavallı herif...";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Dur! Lütfen dur! Beni bağışla! Yemin ederim, beni zorladılar! Silahı kafama dayamışlardı...";
			link.l1 = "Kapa çeneni. Bunu biliyorum. Son piç nerede? Marcello Cyclops nerede?!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Ben... Ben... Bilmiyorum!";
			link.l1 = "Yalan söylüyorsun, pislik! Bunu görebiliyorum. Kiklop nerede?";
			if (pchar.questTemp.LSC.Mary == "die") link.l1.go = "whiskey_10"; // ушел на Флерон
			else link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "O... o, Kapper'den bazı emirler aldı ve gitti. Nerede olduğunu bilmiyorum!";
			link.l1 = "Yine yalan söylüyorsun. Her şeyi biliyorsun. Korkaklık etme, pislik - Kapper öldü ve sana artık zarar veremez. Ama bana Marcello'nun nerede olduğunu söylemezsen, seni burada domuz gibi keserim! Chad, Cyclops'a ne yapmasını emretti?";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "Onu... Kızıl Mary'yi öldürmeye gönderdi.";
			link.l1 = "Ne?! Hemen söyle, bunu nasıl yapacak? Onun kamarasına girmek imkânsız! Onu öldürmeyi nasıl planlıyor?!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			dialog.text = "Demirci dışarıdayken Jurgen’in kamarasına girecek. Sonra ambarın en altına inip oradan geçecek ve Mary’nin kamarasına ulaşacak.\nOndan sonra tek yapması gereken, kızın arkasını dönmesini ya da uykuya dalmasını beklemek olacak. Chad bana böyle söyledi. Başka hiçbir şey bilmiyorum, yemin ederim!";
			link.l1 = "Bu kadar yeter. Ne zaman gitti? Söylesene, Cyclops ne zaman 'Ceres Smithy'ye gitti?";
			link.l1.go = "whiskey_7";
		break;
		
		case "whiskey_7":
			dialog.text = "Şimdiye kadar Jurgen'in kamarasında olmalı... ya da aşağıda, ambarın içinde...";
			link.l1 = "Lanet olsun! Adanın etrafında yüzmeye vaktim yok! Narvallerin gemilerinin şifresini söyle! Konuş, ve bana yalan söylersen, ben bir şekilde kurtulurum ama sen kesinlikle ölürsün!";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "'"+sNrvParol+"'...";
			link.l1 = "Anladım. Şimdi kızın hayatta kalması için dua et.";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "whiskey_repeat";
			pchar.quest.LSC_RescueMary.win_condition.l1 = "location";
			pchar.quest.LSC_RescueMary.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_RescueMary.function = "LSC_RescueMary";
			AddQuestRecord("SharkHunt", "46");
			AddQuestUserData("SharkHunt", "sParol", sNrvParol);
			pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "whiskey_repeat":
			dialog.text = "Sana bildiğim her şeyi zaten anlattım! Yemin ederim!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "whiskey_repeat";
		break;
		
		case "whiskey_10":
			dialog.text = "O... O, 'Fleron'un içinde bir yerde. Chad ona orada saklanmasını ve sonraki emirlerini beklemesini söyledi.";
			link.l1 = "Anladım. Umarım bu doğru söylüyorsundur...";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.LSC_FindCyclop.win_condition.l1 = "location";
			pchar.quest.LSC_FindCyclop.win_condition.l1.location = "FleuronTavern";
			pchar.quest.LSC_FindCyclop.function = "LSC_SetCyclop_Fl";
			NextDiag.CurrentNode = "whiskey_repeat";
			AddQuestRecord("SharkHunt", "51");
			
		break;
		
		// --> конфликты
		case "conflict":
			dialog.text = "Öyle mi? Peki, delikanlı, hangi klan seni rahatsız ediyor?";
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				link.l1 = "Narvaller.";
				link.l1.go = "narval";
				npchar.quest.clan = "narval";
			}
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				link.l2 = "Rivados.";
				link.l2.go = "rivados";
				npchar.quest.clan = "rivados";
			}
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				link.l3 = "Amiralin korsanları.";
				link.l3.go = "shark";
				npchar.quest.clan = "shark";
			}
			link.l4 = "Böyle bir şey yok. Şaka yapıyordum Giuseppe, iyiyim.";
			link.l4.go = "exit";
		break;
		
		case "narval":
			npchar.quest.price = sti(pchar.GenQuest.NarvalConflict)*50;
			if (sti(pchar.GenQuest.NarvalConflict) < 3) dialog.text = "Pek de bir çatışma sayılmaz, sadece ufak bir yanlış anlaşılma, hehe. "+sti(npchar.quest.price)+"  dublon ver, derdin bir günde çözülür.";
			else
			{
				if (sti(pchar.GenQuest.NarvalConflict) >= 3 && sti(pchar.GenQuest.NarvalConflict) < 10) dialog.text = "Elbette, duydum olanları. Epeyce ortalığı karıştırdın, sevgili dostum. Ama bir çıkış yolu var. "+sti(npchar.quest.price)+" dublon ver, derdin bir günde çözülür.";
				else dialog.text = "Tüm ada işlediğin katliamı biliyor. Sana yardım etmek kolay olmayacak, ama bir ihtimal var. "+sti(npchar.quest.price)+" dublon ver, sorununu çözmeye çalışırım.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "Al, paralarını ve hallet şunu.";
				link.l1.go = "pay";
			}
			link.l2 = "Ne yazık ki, şu anda yanımda yeterince dublon yok. Ama sonra getireceğim ve tekrar konuşuruz.";
			link.l2.go = "exit";
		break;
		
		case "rivados":
			npchar.quest.price = sti(pchar.GenQuest.RivadosConflict)*50;
			if (sti(pchar.GenQuest.RivadosConflict) < 3) dialog.text = "Pek de bir çatışma sayılmaz, sadece ufak bir yanlış anlaşılma, he-he. "+sti(npchar.quest.price)+"  dublon ver, derdin bir günde çözülür.";
			else
			{
				if (sti(pchar.GenQuest.RivadosConflict) >= 3 && sti(pchar.GenQuest.RivadosConflict) < 10) dialog.text = "Elbette, duydum. Epey bir karmaşa çıkardın, canım. Ama bir çıkış yolu var. "+sti(npchar.quest.price)+"  dubloonları ver, sorunun bir günde çözülür.";
				else dialog.text = "Tüm ada işlediğin katliamı biliyor. Sana yardım etmek kolay olmayacak, ama bir ihtimal var. "+sti(npchar.quest.price)+" dublon ver, sorununu çözmeye çalışacağım.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "Al bakalım paralarını, kendin hallet.";
				link.l1.go = "pay";
			}
			link.l2 = "Ne yazık ki, şu anda yanımda yeterince dublon yok. Ama sonra getireceğim ve tekrar konuşuruz.";
			link.l2.go = "exit";
		break;
		
		case "shark":
			npchar.quest.price = sti(pchar.GenQuest.SharkConflict)*50;
			if (sti(pchar.GenQuest.SharkConflict) < 3) dialog.text = "Pek de bir çatışma sayılmaz, sadece ufak bir yanlış anlaşılma, hehe. "+sti(npchar.quest.price)+" dublon verin, sorununuz bir gün içinde çözülür.";
			else
			{
				if (sti(pchar.GenQuest.SharkConflict) >= 3 && sti(pchar.GenQuest.SharkConflict) < 10) dialog.text = "Elbette, duydum olanları. Epeyce karışıklık çıkardın, canım. Ama bir çıkış yolu var. "+sti(npchar.quest.price)+" dublon ver, derdin bir günde çözülür.";
				else dialog.text = "Tüm ada işlediğin katliamı biliyor. Sana yardım etmek kolay olmayacak, ama bir ihtimal var. "+sti(npchar.quest.price)+" dublon ver, sorununu çözmeye çalışacağım.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "Al, şu paraları ve işini hallet.";
				link.l1.go = "pay";
			}
			link.l2 = "Maalesef, şu anda yanımda yeterince dublon yok. Ama sonra getireceğim, o zaman tekrar konuşuruz.";
			link.l2.go = "exit";
		break;
		
		case "pay":
			RemoveDublonsFromPCharTotal(sti(npchar.quest.price));
			PlaySound("interface\important_item.wav");
			Log_Info("You have given "+sti(npchar.quest.price)+" doubloons");
			dialog.text = "Harika. Şimdi otur ve biraz dinlen. Senin sorununu çözene kadar kabinimde kalman en iyisi olur. Durumu daha da kötüleştirmene gerek yok, canım.";
			link.l1 = "Peki...";
			link.l1.go = "peace";
		break;
		
		case "peace":
			DialogExit();
			GetCharacterPos(pchar, &locx, &locy, &locz);
			pchar.locx = locx;
			pchar.locy = locy;
			pchar.locz = locz;
			SetLaunchFrameFormParam("One day later..."+ NewStr() +"Fazio has dealt with the conflict", "Reload_To_Location", 0.1, 5.0);
			SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
			WaitDate("", 0, 0, 1, 3, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			switch (npchar.quest.clan)
			{
				case "narval":
					DeleteAttribute(pchar, "GenQuest.NarvalConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") || !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false);//открыть вход к Дональду
					LAi_group_SetRelation("LSC_NARVAL", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "rivados":
					DeleteAttribute(pchar, "GenQuest.RivadosConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend") || !CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload33", false);//открыть вход к Эдди
					LAi_group_SetRelation("LSC_RIVADOS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "shark":
					DeleteAttribute(pchar, "GenQuest.SharkConflict"); // мирим
					LSC_OpenSanAvgustinDoors(); // открыть сан-августин
					LSC_OpenTartarusDoors(); // открыть тартарус
					LAi_group_SetRelation("LSC_SHARK", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
			}
			DeleteAttribute(npchar, "quest.clan");
			DeleteAttribute(npchar, "quest.price");
		break;
		
		// --> пей до дна
		case "drink":
			dialog.text = "Hadi ama, oğlum! Hepsi yalan söylüyor, he-he. Benim kafam biraz daha sağlam olabilir ama ben de senin gibi bir insanım, rom içince sarhoş oluyorum. İnsanlar romu sarhoş olmak için içer, başka bir amacı yoktur. Hiç düşündün mü bunu, canım?";
			link.l1 = "Gerçekten öyle.";
			link.l1.go = "drink_1";
		break;
		
		case "drink_1":
			dialog.text = "Benimle komik bir oyun oynamak ister misin? Adı 'Son Damlasına Kadar İç!', ha-ha! Eminim daha önce duymuşsundur. Yanılıyor muyum?";
			link.l1 = "Evet, bununla ilgili bazı fısıltılar dolaşıyordu... Ben buna 'yüzünü masaya koymak' derim.";
			link.l1.go = "drink_2";
		break;
		
		case "drink_2":
			dialog.text = "Ha-ha-ha, sevgili oğlum, yaşlı adama iyi bir kahkaha attırdın, başka ne diyebilirim ki! 'Yüzün masada!' Bunu unutmayacağım... Peki, ne dersin? Yüz dublon için oynayalım mı?";
			link.l1 = "Yüz dublon mu?";
			link.l1.go = "drink_3";
		break;
		
		case "drink_3":
			dialog.text = "Evet, ve kaybeden içkileri ısmarlıyor. Anlaştık mı?";
			if (PCharDublonsTotal() >= 100)
			{
				link.l1 = "Evet, anlaştık. İşte ortaya koyduğum şey.";
				link.l1.go = "drink_4";
			}
			link.l2 = "Hm. O kadar çok dublonum yok.";
			link.l2.go = "drink_wait";
		break;
		
		case "drink_wait":
			dialog.text = "Peki, onları bulduğunda yanıma gel, birlikte oynarız!";
			link.l1 = "Peki...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Drink = "wait";
		break;
		
		case "drink_4":
			RemoveDublonsFromPCharTotal(100);
			Log_Info("You have given 100 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Harika, sevgili dostum! O zaman saat dokuzda Sancho'nun meyhanesinde buluşalım! Evet, eğer geç kalırsan bahsin bende kalır, bu kurallardan biri. Ama geç kalmazsın, değil mi oğlum?";
			link.l1 = "Tabii Giuseppe. Şişe dövüşüne hazır ol!";
			link.l1.go = "drink_5";
		break;
		
		case "drink_5":
			dialog.text = "Ve sen, ve sen, canım! Yüzün masada! Ha-ha!";
			link.l1 = "Saat dokuzda meyhanede görüşürüz!";
			link.l1.go = "drink_6";
		break;
		
		case "drink_6":
			DialogExit();
			pchar.questTemp.LSC.Drink = "start";
			pchar.quest.LSC_DrinkOver.over = "yes"; //снять таймер
			pchar.quest.LSC_Drink.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink.win_condition.l1.date.hour  = 21.0;
			pchar.quest.LSC_Drink.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink.function = "LSC_DrinkPrepare";
			pchar.quest.LSC_Drink_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.hour  = 23.0;
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink_Over.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "2");
		break;
		
		case "drink_8":
			dialog.text = "Pekâlâ, sevgili dostum, masayı öpmeye hazır mısın, hı-hı? İyi Sancho bize çoktan rom getirdi bile. Kuralları anlatmama gerek yok sanırım? Oldukça basit: Aynı şişeden içeriz, biri devrilene kadar.\nEvet, konuşabiliriz, konuşmalıyız da! Düzgün insanlarla sohbet etmek harika değil mi? Ve kazanırsan, ödülünü Sancho'dan alabilirsin. Hazır mısın?";
			link.l1 = "Bence evet. Hadi başlayalım, Giuseppe!";
			link.l1.go = "drink_9";
		break;
		
		case "drink_9":
			DialogExit();
			pchar.questTemp.LSC.Drink = "go";
			pchar.quest.LSC_Drink_Over.over = "yes"; //снять таймер
			ChangeCharacterAddressGroup(pchar, "FleuronTavern", "quest", "sit1");
			LAi_SetActorType(pchar);
			LAi_ActorSetSitMode(pchar);
			ChangeCharacterAddressGroup(npchar, "FleuronTavern", "quest", "sit2");
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			DoQuestFunctionDelay("LSC_DrinkGo", 0.6);
		break;
		
		case "drunk":
			dialog.text = "On beş adam ölü... hık! Aha! Yo-ho-ho... Ve... şişe...";
			link.l1 = "Muazzam...";
			link.l1.go = "exit";
			NextDiag.TempNode = "drunk";
		break;
		// <-- пей до дна
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
