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
				dialog.text = "O quê? O que você quer?";
				link.l1 = TimeGreeting()+". Meu nome é "+GetFullName(pchar)+". Eu queria conhecer o líder do clã.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! Quer alguma coisa?";
				link.l5 = "Só queria dizer oi. Até mais!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Now you know me. My name is Donald Greenspen, and don't make me or my men angry. And don't try to visit the 'San Gabriel' until you have a password. The shop is open to all; everyone needs to trade. Any questions?";
			link.l2 = "Não, entendi. Até mais.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
	// ----------------------------------после разгрома Чада и Мэри на Каролине---------------------------
		case "shark":
			dialog.text = "Que assunto você tem comigo?";
			link.l1 = "Uma notícia bem desagradável, Donald. Tentaram matar o Steven ontem à noite. Lutadores do seu clã estavam envolvidos.";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "Eu não sei sobre isso. Por que você acha que eles eram meus homens?";
			link.l1 = "Porque eu estava lá. Dá pra ver a diferença entre seus homens, piratas e os Rivados. O grupo era liderado por Mary Casper e Chad Kapper. Precisa de mais provas?";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "Posso apenas garantir que meus homens e eu não temos nada a ver com isso.";
			link.l1 = "Você vai ter que convencer o almirante disso, e não vai ser fácil. Dodson está furioso com todos os Narvais depois do ataque. Ele vai declarar guerra contra vocês – vai parar de fornecer mantimentos e atirar nos seus homens sempre que tiver oportunidade. E não são só palavras.";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "Espero que o almirante saiba o que está fazendo. Será que ele duvida que meus homens sabem atirar tão bem quanto?";
			link.l1 = "Acho que sim. Ele está pronto para transformar o 'San Augustine' numa fortaleza e lutar até vocês morrerem de fome. Além disso, Dodson vai conversar com os Rivados e propor uma aliança. Vocês não terão chance contra o almirante e os Rivados juntos.";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "Porra! Mas nós não temos nada a ver com essa tentativa! Por que todo o clã tem que pagar pelos atos daquela garota idiota, a Mary, e de um bando de canalhas da minha tripulação?\nAlém disso, sejamos lógicos: ao matar Marlow, o próprio Dodson provocou a Mary e meus soldados. É exatamente isso que acontece quando se faz uma canalhice dessas.";
			link.l1 = "Você não entende nada. Você foi enganado. Por que tem tanta certeza de que o Dodson matou o Alan? Na verdade, ele acha que foi você quem fez isso para tomar o lugar dele...";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "Eu não dou a mínima para o que ele pensa. Todas as provas estão contra ele. Só ele e seus homens tinham acesso à prisão. Alan estava nas mãos dele. A Mary Vermelha me contou muita coisa. Antes de Alan ser assassinado, Dodson foi pessoalmente à prisão, e isso não é algo que ele faz com frequência.";
			link.l1 = "Você o viu morrer?";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "Besteira! Claro que não.";
			link.l1 = "E o Chimiset também. Sim, sim, o feiticeiro dos Rivados que estava sentado ao lado do Alan. Ele também foi assassinado lá recentemente. Estive na prisão um dia antes da morte dele e conversei com ele. Milrow foi morto pelo Chad Kapper, o contramestre do Tubarão.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "É verdade?";
			link.l1 = "Pense bem: Chimiset não se importava com o seu relacionamento com o almirante. Ele não tinha motivo para mentir. O velho feiticeiro tinha medo do Chad, achava que seria o próximo. E estava certo, Chad o matou assim que soube que o almirante ia libertá-lo.";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "Mas por que Kapper queria a morte do Alan?";
			link.l1 = "Maldição, você ainda não entendeu? Eu te disse que o Kapper estava trabalhando com a Mary Vermelha. Ele queria tomar o lugar do Tubarão e bolou um plano astuto pra isso. Matar o Alan Milrow e espalhar boatos sobre o envolvimento do Tubarão na morte dele deixou o clã Narval hostil ao almirante...";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			dialog.text = "";
			link.l1 = "Silly girl Mary trusted him and sided with the real killer of her boyfriend. They persuaded a few Narwhals to join them; it must have been easy for Mary. Then they organised an attack on the admiral in Fazio's cabin, where he was forced to write an invitation to the admiral...";
			link.l1.go = "shark_10";
		break;
		
		case "shark_10":
			dialog.text = "";
			link.l1 = "Tenho uma carta do Fazio que explica tudo. Chimiset foi morto pelo Chad por ser uma testemunha perigosa. Ele estava colaborando com os Narvais, e os Rivados vão ficar muito satisfeitos em saber disso durante a conversa com o Tubarão. Vamos provar facilmente para o Eddie Negro que o Chad virou um dos seus mostrando esta carta.";
			link.l1.go = "shark_11";
		break;
		
		case "shark_11":
			dialog.text = "Hm. Você está com todas as cartas na mão, então o que está fazendo aqui? Quer algo de mim, não é?";
			link.l1 = "Eu acredito. Porque acho que tudo isso foi plano do Chad e que você não está envolvido. Chad traiu a Mary, ela chamou amigas do seu clã para ajudá-la, e é só isso. Pelo menos, não encontrei nenhuma prova contra você ou qualquer outro Narval...";
			link.l1.go = "shark_12";
		break;
		
		case "shark_12":
			dialog.text = "";
			link.l1 = "Mas isso não significa que não restaram outros conspiradores. Quero que você os procure. Talvez assim consigamos resolver tudo sem um banho de sangue.";
			link.l1.go = "shark_13";
		break;
		
		case "shark_13":
			dialog.text = "I have already told you that none of my men were involved. After Marlow's death, Mary essentially left the clan and locked herself in her cabin. Honestly, I have no idea how she managed to persuade others to take part in it, but it seems she succeeded. I swear that neither I nor anyone else from my clan is acting against the admiral. We have lost too many men recently, so we don't want to get involved in any messy business now. I am not afraid of the admiral's attack, even if he joins forces with the Rivados. The Narwhals are true warriors, and we will prove that in our last battle. But that would be pointless. We have already decided to keep the peace with the admiral. The Rivados are a different matter; we don't negotiate with Negros. I am ready to apologize to the admiral personally, to ask forgiveness for my suspicions caused by Milrow's death and for the attack on his life. I will swear on the Bible to prove my sincerity. Are you and Dodson fine with that?";
			link.l1 = "Sou eu. Tem certeza de que seus homens não vão tentar nenhuma artimanha?";
			link.l1.go = "shark_14";
		break;
		
		case "shark_14":
			dialog.text = "Com certeza. Vou informar meu clã sobre o verdadeiro assassino de Alan Milrow. A relação dos meus homens com o almirante vai mudar imediatamente, pode acreditar. Me diga, será necessário um massacre depois disso?";
			link.l1 = "Não, não vai acontecer. Estou aqui para impedir isso. Confio em você, Donald, e vou tentar convencer o Tubarão. Ainda tenho alguns argumentos... Até logo, Donald!";
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
			dialog.text = "Já falou com o almirante? Teve algum resultado?";
			link.l1 = "Estou avançando. Nos vemos mais tarde...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "shark_16":
			dialog.text = "Já falou com o almirante? Teve algum resultado?";
			link.l1 = "Sim, eu ouvi. Seu pedido de desculpas foi aceito, e a acusação do seu clã foi retirada. Tem mais: Tubarão convida você para encontrá-lo e discutir os termos de um futuro acordo de paz entre os Narvais e os piratas.";
			link.l1.go = "shark_17";
		break;
		
		case "shark_17":
			dialog.text = "Para ser sincero, eu não esperava... Isso é uma ótima notícia. Talvez até possamos reconsiderar os preços dos mantimentos para o nosso clã e uma nova política em relação aos Rivados.";
			link.l1 = "Isso diz respeito apenas a você e ao almirante.";
			link.l1.go = "shark_18";
		break;
		
		case "shark_18":
			dialog.text = "Sim, claro. Você prestou um grande serviço ao clã Narval ao evitar um derramamento de sangue desnecessário e talvez até mesmo a aniquilação total dos meus homens. Aceite este mosquete de torre como prova da minha gratidão, você não encontrará outra arma como esta\nAlém disso, você agora pode visitar nossas áreas restritas como qualquer outro membro do clã.";
			link.l1 = "Obrigado! Até logo, tenho muitas coisas para fazer.";
			link.l1.go = "shark_19";
		break;
		
		case "shark_19":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower mousqueton");
			PlaySound("interface\important_item.wav");
			dialog.text = "Boa sorte. Fale comigo se tiver alguma dúvida.";
			link.l1 = "Entendi. Até mais!";
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
				dialog.text = "Ei! "+GetFullName(pchar)+"! Você é... não, não pode ser! Você está vivo?!";
				link.l1 = "Os boatos sobre a minha morte foram um pouco exagerados, Donald. Ha-ha, bom te ver!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "A-ah, meu amigo "+GetFullName(pchar)+"! Precisa de alguma coisa?";
			link.l1 = "Não, não quero nada. Só queria te cumprimentar.";
			link.l1.go = "exit";
			NextDiag.TempNode = "grinspy_wait";
		break;
		
		case "negotiations":
			dialog.text = "Que assunto você tem comigo?";
			link.l1 = "Uma notícia muito desagradável, Donald. Tentaram matar o Steven. Lutadores do seu clã estavam envolvidos.";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			dialog.text = "Não sei sobre isso. Por que você acha que meus homens estavam envolvidos?";
			link.l1 = "Porque eu mesmo matei alguns deles junto com Chad Kapper, o contramestre do almirante que é o responsável por toda essa confusão. Ele não conseguiu fazer isso sozinho, então seus homens ajudaram muito. O almirante sabe disso e está muito, mas muito furioso.";
			link.l1.go = "negotiations_2";
		break;
		
		case "negotiations_2":
			dialog.text = "Meus homens? Quem exatamente? Pode dizer quem são?";
			link.l1 = "Eles nem se apresentaram. Só chegaram atirando e lutando de espada. Seu povo é imprudente. São capazes até de atacar um dos seus. Ora, comigo ou com o almirante, tudo bem, mas tentar matar a garota?";
			link.l1.go = "negotiations_3";
		break;
		
		case "negotiations_3":
			dialog.text = "Hum. De quem você está falando?";
			if (pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "De quem estou falando? Estou falando do ataque à Mary Vermelha. Dois Narvais tentaram matá-la. Cheguei à cabine dela num momento crítico, totalmente por acaso. Eles teriam matado ela se eu tivesse chegado um pouco mais tarde. Não perguntei os nomes deles, me desculpe, não tive tempo de conversar com eles, mas a Mary disse que eram Narvais.";
				link.l1.go = "negotiations_4";
			}
			else
			{
				link.l1 = "De quem estou falando? Estou falando do ataque à Mary Vermelha e daqueles dois Narvais que a mataram."link.l1.go ="negotiations_6";
			}
		break;
		
		case "negotiations_4":
			dialog.text = "O quê? Por que ela não me contou?! Eu teria agido na hora!";
			link.l1 = "Ela estava com medo até de sair da própria cabine esses dias. Vocês discutiram há pouco tempo, então por que ela iria te procurar e pedir ajuda?";
			link.l1.go = "negotiations_5";
		break;
		
		case "negotiations_5":
			dialog.text = "Eu não discuti com ela! Ela exigiu o impossível de mim, tivemos uma conversa difícil e eu a mandei embora. Mas isso não significa que eu...";
			link.l1 = "Tudo bem, tanto faz. Afinal, todos os problemas já foram resolvidos. Mas tem canalhas entre os seus homens, isso é fato.";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_6":
			dialog.text = "O quê? Ela foi morta pelos Narvais? Por quê?";
			link.l1 = "Por ordem de Chad Kapper, Donald. Ela sabia demais e se recusou a ajudar o Chad. E agora a pobre garota está morta!";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_7":
			dialog.text = "Juro, eu não sabia disso!";
			link.l1 = "Claro, você não fez isso... Mas vamos falar do almirante. Chad Kapper organizou a tentativa e seus homens ajudaram ele. Tentaram envenenar o Dodson e eu mal consegui impedir.";
			link.l1.go = "negotiations_8";
		break;
		
		case "negotiations_8":
			dialog.text = "Eu não pedi nada disso. Dodson sabe que não apoio a política do falecido Alan, e acho que um acordo enxuto é melhor do que uma longa disputa.";
			link.l1 = "Você vai ter que convencer o almirante, e isso não vai ser fácil. Dodson está furioso com todos os Narvais depois da tentativa. Ele vai declarar guerra contra vocês.";
			link.l1.go = "negotiations_9";
		break;
		
		case "negotiations_9":
			dialog.text = "Espero que o almirante entenda o que está fazendo. Será que ele duvida que meus homens sabem revidar?";
			link.l1 = "Ele acha que sim. Ele pensa que seu clã é uma quadrilha de bandidos e precisa ser destruído antes que vocês comecem a matar todo mundo. Além disso, temos laços fortes com os Rivados. Posso simplesmente conversar com o Eddie Negro e propor uma aliança. Você não vai conseguir enfrentar todos nós.";
			link.l1.go = "negotiations_10";
		break;
		
		case "negotiations_10":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Call Red Mary if you don't believe me and ask her! She will confirm.";
			else sTemp = "I have a letter from Chad to Mary which proves everything.";
			dialog.text = "Porra! Por que todo o clã tem que pagar pelos erros de alguns idiotas? Não pense que estou com medo. Somos guerreiros, e vamos provar isso mesmo na nossa última batalha. Mas eu quero justiça. Na verdade, o almirante é o responsável por matar Alan Milrow na prisão.";
			link.l1 = "Como você pode ser o líder, Donald... Você não sabe nada sobre a Mary ou o Alan. Chad Kapper matou ele. "+sTemp+" Ele fez isso para virar os Narvais contra o almirante e atrair alguns deles para o seu lado.";
			link.l1.go = "negotiations_11";
		break;
		
		case "negotiations_11":
			dialog.text = "Entendi. Tudo bem. Vamos conversar de outro jeito. Você está aqui por um motivo, certo? O que você quer?";
			link.l1 = "Eu não quero um banho de sangue na ilha. Não quero ver pessoas morrendo. Não gosto da ideia de eliminar todos os Narvais, embora eu te assegure que os Rivados e nós somos capazes disso. Também acho que o clã inteiro não deve pagar pelos atos de alguns canalhas...";
			link.l1.go = "negotiations_12";
		break;
		
		case "negotiations_12":
			dialog.text = "";
			link.l1 = "Mas meu voto não será suficiente – você precisa garantir oficialmente ao almirante que a tentativa não foi aprovada por você e que seu clã não está planejando matar o Dodson.";
			link.l1.go = "negotiations_13";
		break;
		
		case "negotiations_13":
			dialog.text = "O que posso fazer? Estou pronto para pedir desculpas pela tentativa e pelas minhas suspeitas sobre a morte de Marlow. Posso garantir a ele que os Narvais não estão tramando nada contra ele, e juro pela Santa Bíblia. Você e Dodson acham que isso é suficiente?";
			link.l1 = "Eu vou. Tenho certeza de que funcionará com Dodson também, se você for falar com ele pessoalmente. Mas antes, vou contar a ele sobre suas intenções e depois volto para te contar o que aconteceu.";
			link.l1.go = "negotiations_14";
		break;
		
		case "negotiations_14":
			dialog.text = "Tudo bem. Eu vou esperar.";
			link.l1 = "Eu volto logo...";
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
			dialog.text = "Já falou com o almirante? Teve algum resultado?";
			link.l1 = "Sim, já falei com ele. Se você fizer uma visita oficial, então o problema estará resolvido.";
			link.l1.go = "negotiations_18";
		break;
		
		case "negotiations_18":
			dialog.text = "Para ser sincero, eu não esperava... Isso é uma ótima notícia.";
			link.l1 = "Sim, sabe, eu também fico feliz.";
			link.l1.go = "negotiations_19";
		break;
		
		case "negotiations_19":
			dialog.text = "Você prestou um grande serviço ao clã Narval ao impedir um massacre sem sentido e, talvez, até mesmo o extermínio total do meu povo. Eu lhe concedo este mosquete da torre – não encontrará outra arma igual a esta. Você também tem permissão para visitar nossos navios sem qualquer restrição.";
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				link.l1 = "Obrigado. Um presente muito valioso. Sim, Donald, mais uma coisa: faça as pazes com a Mary Vermelha. Ela é explosiva, mas também é sincera e honesta. Discutir com você a fez sair do clã, e isso quase custou a vida dela.";
				link.l1.go = "negotiations_20";
			}
			else
			{
				link.l1 = "Obrigado. Este é um presente muito valioso. E fico realmente feliz que tudo tenha terminado tão bem.";
				link.l1.go = "negotiations_21";
			}
		break;
		
		case "negotiations_20":
			dialog.text = "Diga a ela que peço perdão por tê-la magoado e por aqueles dois canalhas que ousaram atacá-la. Vocês são... amigos, não é?";
			link.l1 = "Você está certo, Donald. Eu vou contar para ela. E fico realmente feliz que tudo tenha terminado tão bem.";
			link.l1.go = "negotiations_21";
		break;
		
		case "negotiations_21":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower musket");
			PlaySound("interface\important_item.wav");
			dialog.text = "Boa sorte. Fale comigo se tiver alguma dúvida.";
			link.l1 = "Tudo bem. Adeus!";
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
			dialog.text = LinkRandPhrase("O que você está fazendo aí, hein? Ladrão!","Olha só! Assim que me perdi em contemplação, você resolveu mexer no meu baú!","Veio mexer nos meus baús? Não vai sair impune!");
			link.l1 = "Merda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "O quê?! Veio fuçar nos meus baús? Você não vai sair impune!";
			link.l1 = "Garota tola!";
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
			dialog.text = LinkRandPhrase("Olha, é melhor você guardar sua arma. Isso me deixa nervoso.","Sabe, andar por aí com uma lâmina não é permitido aqui. Guarde isso.","Escuta, não fique bancando um cavaleiro medieval correndo por aí com uma espada. Guarda isso, não combina com você...");
			link.l1 = LinkRandPhrase("Tudo bem.","Claro.","Como você diz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escute, eu sou um cidadão desta cidade e gostaria que você abaixasse sua espada.","Escute, eu sou um cidadão desta cidade e gostaria que você baixasse sua lâmina.");
				link.l1 = LinkRandPhrase("Tudo bem.","Claro.","Como você diz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Cuidado, amigo, andando por aí com uma arma. Isso me deixa nervoso...","Eu não gosto quando homens passam na minha frente com as armas em punho. Isso me assusta...");
				link.l1 = RandPhraseSimple("Entendi.","Eu vou levar isso.");
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
