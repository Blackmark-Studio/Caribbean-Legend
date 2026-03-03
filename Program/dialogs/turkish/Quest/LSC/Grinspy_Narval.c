// Дональд Гринспи - лидер нарвалов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

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
				dialog.text = "Ne? Ne istiyorsun?";
				link.l1 = TimeGreeting()+" . Benim adım "+GetFullName(pchar)+". Klanın lideriyle tanışmak istedim.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+" ! Bir şey mi istiyorsun? ";
				link.l5 = "Sadece merhaba demek istedim. Görüşürüz!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Now you know me. My name is Donald Greenspen, and don't make me or my men angry. And don't try to visit the 'San Gabriel' until you have a password. The shop is open to all; everyone needs to trade. Any questions?";
			link.l2 = "Hayır, anladım. Görüşürüz.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
	// ----------------------------------после разгрома Чада и Мэри на Каролине---------------------------
		case "shark":
			dialog.text = "Benimle ne işin var?";
			link.l1 = "Çok tatsız bir durum, Donald. Dün gece Steven'ın hayatına kast edildi. Klanından savaşçılar bu işe karışmış.";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "Bu konuda bir fikrim yok. Neden onların benim adamlarım olduğunu düşünüyorsun?";
			link.l1 = "Çünkü oradaydım. Adamlarınız, korsanlar ve Rivados arasındaki farkı görebiliyoruz. Gruba Mary Casper ve Chad Kapper liderlik ediyordu. Daha fazla kanıta ihtiyacınız var mı?";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "Sana sadece, adamlarım ve benim bununla hiçbir ilgimiz olmadığından emin olabilirim.";
			link.l1 = "Bunu amirale kendin anlatman gerekecek, hem de hiç kolay olmayacak. Dodson, saldırıdan sonra tüm Narvalara karşı çok öfkeli. Sana savaş ilan etmeye hazırlanıyor – artık sana erzak vermeyecek ve fırsat buldukça adamlarını vuracak. Ve bunlar sadece lafta kalmayacak.";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "Umarım amiral ne yaptığını biliyordur. Adamlarımın da en az onlar kadar iyi nişan alabildiğinden şüphesi mi var?";
			link.l1 = "Bence öyle. 'San Augustine'i bir kaleye çevirmeye ve hepiniz açlıktan kırılana kadar savaşmaya hazır. Ayrıca, Dodson Rivados'la konuşup onlara iş birliği teklif edecek. Amiral ve Rivados'a karşı birlikte hiç şansınız olmaz.";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "Lanet olsun! Ama biz bu işe karışmadık ki! Neden bütün klan o aptal kız Mary ve tayfamdan birkaç pisliğin yüzünden bedel ödemek zorunda?\nAyrıca, mantıklı düşünelim, Marlow'u öldürerek Dodson bizzat Mary'yi ve askerlerimi kışkırttı. Böyle alçaklıklar yaparsan, olan tam da budur.";
			link.l1 = "Hiçbir şey anlamıyorsun. Kandırılmışsın. Dodson'ın Alan'ı öldürdüğünden neden bu kadar eminsin? Aslında, onun yerini almak için bunu senin yaptığını düşünüyor...";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "Ne düşündüğü umurumda değil. Tüm kanıtlar ona karşı. Hapishaneye sadece o ve adamları girebiliyordu. Alan onun elindeydi. Kızıl Mary bana çok şey anlattı. Alan öldürülmeden önce Dodson şahsen hapishaneye gitmiş, ki bunu sık sık yapmaz.";
			link.l1 = "Onu ölürken gördün mü?";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "Saçmalık! Tabii ki yapmadım.";
			link.l1 = "Ve Chimiset de. Evet, evet, Alan'ın yanında oturan Rivados'un büyücüsü. O da yakın zamanda orada öldürüldü. Ölümünden bir gün önce hapishanedeydim ve onunla konuştum. Milrow'u, Köpekbalığı'nın lostromosu Chad Kapper öldürdü.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "Doğru mu?";
			link.l1 = "Bir düşün: Chimiset senin amiralle olan ilişkinle ilgilenmiyordu. Yalan söylemesi için bir sebebi yoktu. Yaşlı büyücü Chad'den korkuyordu, sıranın kendisine geleceğini düşünüyordu. Haklıydı, Chad amiralin onu serbest bırakacağını öğrenir öğrenmez onu öldürdü.";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "Ama Kapper neden Alan'ın ölümünü istedi?";
			link.l1 = "Lanet olsun, gerçekten anlamıyor musun? Sana Kapper'ın Kızıl Mary ile işbirliği yaptığını söyledim. Köpekbalığı'nın yerini almak istiyordu ve bunu başarmak için kurnazca bir plan yaptı. Alan Milrow'u öldürüp ölümünde Köpekbalığı'nın parmağı olduğuna dair söylentiler yaymak, Narval klanını amirale karşı düşman etti...";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			dialog.text = "";
			link.l1 = "Silly girl Mary trusted him and sided with the real killer of her boyfriend. They persuaded a few Narwhals to join them; it must have been easy for Mary. Then they organised an attack on the admiral in Fazio's cabin, where he was forced to write an invitation to the admiral...";
			link.l1.go = "shark_10";
		break;
		
		case "shark_10":
			dialog.text = "";
			link.l1 = "Fazio’dan her şeyi açıklayan bir mektubum var. Chimiset, tehlikeli bir tanık olduğu için Chad tarafından öldürüldü. O, Narvallerle iş birliği yapıyordu ve Rivados, Shark’la konuşurken bunu duymaktan çok memnun olacak. Bu mektubu göstererek Kara Eddie’ye, Chad’in artık sizden biri olduğunu kolayca kanıtlayacağız.";
			link.l1.go = "shark_11";
		break;
		
		case "shark_11":
			dialog.text = "Hm. Bütün kozlar sende, peki o zaman burada ne işin var? Benden bir şey istiyorsun, değil mi?";
			link.l1 = "Evet, inanıyorum. Çünkü tüm bunların Chad'in planı olduğuna ve senin işin olmadığına inanıyorum. Chad, Mary'yi aldattı, Mary de senin klanından arkadaşlarını yardım için çağırdı, hikaye bu kadar. En azından, şu ana kadar senin ya da başka bir Narval'ın suçuna dair bir kanıt bulamadım...";
			link.l1.go = "shark_12";
		break;
		
		case "shark_12":
			dialog.text = "";
			link.l1 = "Ama bu, başka entrikacıların kalmadığı anlamına gelmez. Onları bulmanı istiyorum. Belki o zaman, işleri kan dökmeden halledebiliriz.";
			link.l1.go = "shark_13";
		break;
		
		case "shark_13":
			dialog.text = "I have already told you that none of my men were involved. After Marlow's death, Mary essentially left the clan and locked herself in her cabin. Honestly, I have no idea how she managed to persuade others to take part in it, but it seems she succeeded. I swear that neither I nor anyone else from my clan is acting against the admiral. We have lost too many men recently, so we don't want to get involved in any messy business now. I am not afraid of the admiral's attack, even if he joins forces with the Rivados. The Narwhals are true warriors, and we will prove that in our last battle. But that would be pointless. We have already decided to keep the peace with the admiral. The Rivados are a different matter; we don't negotiate with Negros. I am ready to apologize to the admiral personally, to ask forgiveness for my suspicions caused by Milrow's death and for the attack on his life. I will swear on the Bible to prove my sincerity. Are you and Dodson fine with that?";
			link.l1 = "Benim. Adamlarından bir hile beklemeyeceğime emin misin?";
			link.l1.go = "shark_14";
		break;
		
		case "shark_14":
			dialog.text = "Elbette. Alan Milrow'un asıl katilini klanıma bildireceğim. Adamlarımın amiralle olan ilişkisi hemen değişecek, buna emin olabilirsin. Söyle bana, bundan sonra bir katliam gerekecek mi?";
			link.l1 = "Hayır, olmayacak. Bunu engellemek için buradayım. Sana güveniyorum Donald, ve Köpekbalığı'nı ikna etmeye çalışacağım. Hâlâ birkaç kozum var... Görüşürüz Donald!";
			link.l1.go = "shark_15";
		break;
		
		case "shark_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "narval"; // ноду Акуле
			AddQuestRecord("SharkHunt", "26");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "narval_wait":
			dialog.text = "Amiralle konuştun mu? Bir sonuç var mı?";
			link.l1 = "İlerleme kaydediyorum. Sonra görüşürüz...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "shark_16":
			dialog.text = "Amiralle konuştun mu? Bir sonuç alabildin mi?";
			link.l1 = "Evet, ettim. Özrünüz kabul edildi, klanınızın ithamı geri çekildi. Dahası da var: Köpekbalığı sizi onunla buluşmaya ve Narvaller ile korsanlar arasındaki gelecekteki barış anlaşmasının şartlarını konuşmaya davet ediyor.";
			link.l1.go = "shark_17";
		break;
		
		case "shark_17":
			dialog.text = "Doğrusunu söylemek gerekirse, bunu beklemiyordum... Bu harika bir haber. Belki de artık klanımız için erzak fiyatlarını ve Rivados'a dair yeni bir politikayı gözden geçirebiliriz.";
			link.l1 = "Bu sadece seni ve amirali ilgilendirir.";
			link.l1.go = "shark_18";
		break;
		
		case "shark_18":
			dialog.text = "Evet, elbette. Narval klanına büyük bir iyilik yaptın; anlamsız bir kan dökülmesini ve belki de adamlarımın tamamen yok olmasını engelledin. Minnettarlığımın bir göstergesi olarak bu kuleli tüfeği al, böylesini başka yerde bulamazsın\nAyrıca, artık diğer klan üyeleri gibi bizim yasaklı bölgelerimize de girebilirsin.";
			link.l1 = "Teşekkürler! Şimdilik hoşça kal, yapacak çok işim var.";
			link.l1.go = "shark_19";
		break;
		
		case "shark_19":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower mousqueton");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bol şans. Bir sorunuz olursa yanıma gelin.";
			link.l1 = "Anladım. Görüşürüz!";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("They say that you are a friend of Donald, Greenspen, the leader of Narwhals. Well, Rivados hate you now...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are Narwhal now. Or do you serve under admiral's command? I don't get it...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I've heard that you have made peace between admiral and Narwhals. Hm, Rivados must be insane about that...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("So Chad Kapper was a murderer of Alan Milrow! That is surprising!", "LostShipsCity", 5, 2, "LSC", "");
		break;
		
		case "grinspy_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ho! "+GetFullName(pchar)+"! Sen... hayır, olamaz! Yaşıyor musun?!";
				link.l1 = "Ölümümle ilgili söylentiler biraz abartılmış, Donald. Ha-ha, seni görmek güzel!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "A-ah, dostum "+GetFullName(pchar)+" ! Bir şeye mi ihtiyacın var?";
			link.l1 = "Hayır, istemiyorum. Sadece seni selamlamak istedim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "grinspy_wait";
		break;
		
		case "negotiations":
			dialog.text = "Benimle ne işin var?";
			link.l1 = "Çok tatsız bir durum, Donald. Steven'ın hayatına bir suikast girişimi oldu. Klanından savaşçılar da bu işe karışmış.";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			dialog.text = "Bu konuda bir fikrim yok. Adamlarımın bu işe karıştığını neden düşünüyorsun?";
			link.l1 = "Çünkü ben şahsen birkaçını Chad Kapper’la birlikte öldürdüm, bütün bu karmaşadan sorumlu olan amiralin lostromosu. Bunu tek başına yapamazdı, bu yüzden adamlarınız ona çok yardım etti. Amiralin bundan haberi var ve çok, ama çok öfkeli.";
			link.l1.go = "negotiations_2";
		break;
		
		case "negotiations_2":
			dialog.text = "Adamlarım mı? Kimden bahsediyorsun? İsimlerini sayabilir misin?";
			link.l1 = "Kendilerini tanıtmadılar. Sadece ateş edip kılıç sallıyorlardı. Sizin insanlarınız çok düşüncesiz. Hatta kendi adamlarına bile saldırabiliyorlar. Benimle ya da amiralle uğraşsalar neyse de, o kızı öldürmeye kalkmak da neyin nesi?";
			link.l1.go = "negotiations_3";
		break;
		
		case "negotiations_3":
			dialog.text = "Hm. Kimden bahsediyorsun?";
			if (pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "Kimden mi bahsediyorum? Kırmızı Mary'ye yapılan saldırıdan bahsediyorum. İki Narval onu öldürmeye çalıştı. Tamamen tesadüf eseri, kritik bir anda kulübesine ulaştım. Biraz daha geç kalsam, onu öldüreceklerdi. İsimlerini sormadım, üzgünüm, onlarla konuşacak vaktim yoktu, ama Mary onların Narval olduğunu söyledi.";
				link.l1.go = "negotiations_4";
			}
			else
			{
				link.l1 = "Kimden mi bahsediyorum? Kırmızı Mary'ye yapılan saldırıdan ve onu öldüren o iki Narval'dan bahsediyorum."link.l1.go ="negotiations_6";
			}
		break;
		
		case "negotiations_4":
			dialog.text = "Ne? Neden bana söylemedi ki?! Hemen harekete geçerdim!";
			link.l1 = "Son zamanlarda kamarasından çıkmaya bile korkuyordu. Seninle kısa süre önce tartıştı, peki neden sana koşup yardımını istesin ki?";
			link.l1.go = "negotiations_5";
		break;
		
		case "negotiations_5":
			dialog.text = "Ben onunla tartışmadım! Benden imkânsızı istedi, aramızda sert bir konuşma geçti ve onu gönderdim. Ama bu, benim...";
			link.l1 = "Pekâlâ, neyse. Sonuçta, artık tüm sorunlar çözüldü. Ama adamlarının arasında alçaklar var, bu bir gerçek.";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_6":
			dialog.text = "Ne? Onu narvaller mi öldürdü? Neden?";
			link.l1 = "Chad Kapper'ın emriyle, Donald. Çok fazla şey biliyordu ve Chad'e yardım etmeyi reddetti. Şimdi ise zavallı kız öldü!";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_7":
			dialog.text = "Yemin ederim, bundan haberim yoktu!";
			link.l1 = "Eminim, öyle yapmadın... Ama amiralle ilgili konuşalım. Chad Kapper bu girişimi organize etti ve adamların ona yardım etti. Dodson'u zehirlemeye çalıştılar ve bunu zar zor engelledim.";
			link.l1.go = "negotiations_8";
		break;
		
		case "negotiations_8":
			dialog.text = "Ben öyle bir şey sipariş etmedim. Dodson, merhum Alan'ın politikasını desteklemediğimi bilir ve bence zayıf bir uzlaşma, şişkin bir davadan iyidir.";
			link.l1 = "Amirali ikna etmen gerekecek, bu hiç de kolay olmayacak. Dodson, girişimden sonra tüm Narvaller'e karşı öfkeli. Sana savaş ilan etmeye hazırlanıyor.";
			link.l1.go = "negotiations_9";
		break;
		
		case "negotiations_9":
			dialog.text = "Umarım amiral yaptıklarının farkındadır. Adamlarımın karşılık veremeyeceğinden mi şüphe ediyor?";
			link.l1 = "Evet, öyle düşünüyor. Klanınızı bir haydut çetesi olarak görüyor ve herkesin canına kıymadan önce yok edilmesi gerektiğine inanıyor. Ayrıca, Rivados ile güçlü bağlarımız var. Siyah Eddie ile konuşup ona bir ittifak teklif edebilirim. Hepimize karşı duramazsınız.";
			link.l1.go = "negotiations_10";
		break;
		
		case "negotiations_10":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Call Red Mary if you don't believe me and ask her! She will confirm.";
			else sTemp = "I have a letter from Chad to Mary which proves everything.";
			dialog.text = "Lanet olsun! Neden bütün klan birkaç aptalın yüzünden bedel ödemek zorunda? Korktuğumu sanma. Biz savaşçıyız ve bunu son savaşımızda bile kanıtlayacağız. Ama ben adalet istiyorum. Aslında, hapishanede Alan Milrow'u öldürenin sorumlusu amiral.";
			link.l1 = "Sen nasıl lider olabilirsin Donald... Mary ya da Alan hakkında hiçbir şey bilmiyorsun. Chad Kapper onu öldürdü. "+sTemp+" Bunu, Narvalları amirale karşı çevirmek ve bazılarını kendi tarafına çekmek için yaptı.";
			link.l1.go = "negotiations_11";
		break;
		
		case "negotiations_11":
			dialog.text = "Anladım. Peki. Başka türlü konuşalım. Buraya bir sebeple geldin, değil mi? Ne istiyorsun?";
			link.l1 = "Adada kanlı bir karmaşa istemiyorum. İnsanların ölmesini istemiyorum. Tüm Narvaları ortadan kaldırma fikrinden hoşlanmıyorum, ama emin ol, Rivados ve biz bunu yapabiliriz. Ayrıca, birkaç alçağın yaptıklarından dolayı bütün bir klanın sorumlu tutulmaması gerektiğini düşünüyorum...";
			link.l1.go = "negotiations_12";
		break;
		
		case "negotiations_12":
			dialog.text = "";
			link.l1 = "Ama benim oyum yeterli olmayacak - amirale resmen güvence vermelisin ki bu girişim senin onayınla yapılmadı ve klanın Dodson'ı öldürmeyi planlamıyor.";
			link.l1.go = "negotiations_13";
		break;
		
		case "negotiations_13":
			dialog.text = "Ne yapabilirim? Girişimim ve Marlow’un ölümüyle ilgili şüphelerim için özür dilemeye hazırım. Narvallerin ona karşı bir şey planlamadıklarına onu temin edebilirim, hatta Kutsal Kitap üzerine yemin ederim. Bu, senin ve Dodson’ın için yeterli olacak mı?";
			link.l1 = "Yaparım. Eminim, Dodson'a da bizzat giderseniz işe yarayacaktır. Ama önce ona niyetlerinizden bahsedeceğim, sonra da sonuçlarla birlikte tekrar sizi ziyaret edeceğim.";
			link.l1.go = "negotiations_14";
		break;
		
		case "negotiations_14":
			dialog.text = "Pekâlâ. Bekleyeceğim.";
			link.l1 = "Yakında döneceğim...";
			link.l1.go = "negotiations_15";
		break;
		
		case "negotiations_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "peace"; // ноду Акуле
			sld = characterFromId("Dexter");
			sld.dialog.currentnode = "First time"; 
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto11");
			AddQuestRecord("SharkHunt", "56");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "negotiations_17":
			dialog.text = "Amiralle konuştun mu? Bir sonuç var mı?";
			link.l1 = "Evet, gördüm. Ona resmi bir ziyaret yaparsan, sorun çözülür.";
			link.l1.go = "negotiations_18";
		break;
		
		case "negotiations_18":
			dialog.text = "Açıkçası, beklemiyordum... Bu harika bir haber.";
			link.l1 = "Evet, biliyor musun, ben de memnunum.";
			link.l1.go = "negotiations_19";
		break;
		
		case "negotiations_19":
			dialog.text = "Anlamsız bir katliamı ve belki de halkımın tamamen yok edilmesini engelleyerek Narval klanına büyük bir iyilik yaptın. Sana bu kuleli tüfeği veriyorum - böylesini başka yerde bulamazsın. Ayrıca gemilerimizi de dilediğin gibi ziyaret edebilirsin.";
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				link.l1 = "Teşekkürler. Çok değerli bir hediye. Evet, Donald, bir şey daha: Kızıl Mary ile barış. O biraz öfkeli, ama aynı zamanda samimi ve dürüst biri. Seninle tartışması onu klanı terk etmeye itti ve bu neredeyse hayatına mal oluyordu.";
				link.l1.go = "negotiations_20";
			}
			else
			{
				link.l1 = "Teşekkür ederim. Bu gerçekten çok değerli bir hediye. Ve her şeyin böyle güzel sonuçlanmasına gerçekten sevindim.";
				link.l1.go = "negotiations_21";
			}
		break;
		
		case "negotiations_20":
			dialog.text = "Ona, onu incittiğim ve ona saldırmaya cüret eden o iki pislik için affını dilediğimi söyle. Siz ikiniz... arkadaşsınız, değil mi?";
			link.l1 = "Haklısın, Donald. Ona söyleyeceğim. Ve her şeyin bu kadar iyi sonuçlanmasına gerçekten çok sevindim.";
			link.l1.go = "negotiations_21";
		break;
		
		case "negotiations_21":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower musket");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bol şans. Bir sorunuz olursa yanıma gelin.";
			link.l1 = "Pekala. Hoşça kal!";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			sld = characterFromId("Mary");
			sld.quest.donald = "true";
			LocatorReloadEnterDisable("CeresSmithy", "reload3", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload4", false); // открываем Церес изнутри
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			// здесь почищу весь хлам, который накопился
			DeleteAttribute(pchar, "questTemp.LSC.Donald_enter"); // атрибут гардов
			DeleteAttribute(pchar, "questTemp.LSC.Florentina");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_poison");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_warning");
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			DeleteAttribute(pchar, "questTemp.LSC.CapperDie_Aeva");
			AddSimpleRumourCityTip("They say that you are a friend of Donald, Greenspen, the leader of Narwhals. Well, Rivados hate you now...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are Narwhal now. Or do you serve under admiral's command? I don't get it...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I've heard that you have made peace between admiral and Narwhals. Hm, Rivados must be insane about that...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("So Chad Kapper was a murderer of Alan Milrow! That is surprising!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("Take care of Red Mary cause you are lucky to be with her - she is so reckless! She always gets in trouble...", "LostShipsCity", 20, 5, "LSC", "");
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Orada ne yapıyorsun, ha? Hırsız!","Şuna bak! Ben dalıp gitmişken, hemen sandığımı karıştırmaya kalktın!","Sandıklarımı mı kurcalamaya karar verdin? Bunu yanına bırakmam!");
			link.l1 = "Kahretsin!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ne?! Sandıklarımı mı karıştırmaya geldin? Bunu sana yedirtmem!";
			link.l1 = "Ahmak kız!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Dinle, silahını yerine koysan iyi edersin. Bu beni tedirgin ediyor.","Biliyor musun, burada elinde bıçakla dolaşmana izin verilmez. Onu kaldır.","Dinle, elinde kılıçla etrafta dolaşan bir ortaçağ şövalyesi gibi davranma. Onu yerine koy, sana yakışmıyor...");
			link.l1 = LinkRandPhrase("Peki.","Tabii.","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dinle, ben bu şehrin bir vatandaşıyım ve senden kılıcını indirmeni rica ediyorum.","Dinle, ben bu şehrin bir vatandaşıyım ve senden kılıcını indirmeni rica ediyorum.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Tabii.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dikkatli ol dostum, elinde silahla dolaşmak beni tedirgin ediyor...","Silahları çekilmiş adamların önümden geçmesini sevmem. Bu beni korkutuyor...");
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
