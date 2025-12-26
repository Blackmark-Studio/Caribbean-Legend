// диалоги НПС по квесту НСО
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
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
			dialog.text = "O que você está procurando?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		// инспектор Ноэль Форже
		case "noel":
			dialog.text = "Prazer em conhecê-lo, capitão!";
			link.l1 = "Também fico feliz em conhecê-lo, Monsieur Forget. É raro encontrar um visitante vindo da metrópole aqui neste fim de mundo...";
			link.l1.go = "noel_1";
		break;
		
		case "noel_1":
			DialogExit();
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_3";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "noel_2":
			dialog.text = "Fico feliz por estar a bordo do seu navio nesta jornada, capitão. Chevalier de Poincy me contou muitas histórias interessantes sobre você. Tenho certeza de que, depois do jantar no refeitório, teremos muitos assuntos para conversar. Uma taça de vinho também cairia bem.";
			link.l1 = "Sempre topo uma boa conversa, ainda mais de barriga cheia. Vou adorar ser sua companhia, Barão. ";
			link.l1.go = "noel_3";
		break;
		
		case "noel_3":
			dialog.text = "Perfeito. Quando chegarmos a uma colônia, vou pedir que me leve até o governador, e eu mesmo vou explicar a ele o que precisa ser feito. Você só precisa esperar até eu terminar meus assuntos. Combinado?";
			link.l1 = "Bem-vindo a bordo, Monsieur Forget!";
			link.l1.go = "noel_4";
		break;
		
		case "noel_4":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 12.0);
		break;
		
		case "noel_5":
			dialog.text = "Tortuga é uma colônia pequena, Capitão. Estimo que vou precisar de uns três dias para inspecionar tudo o que preciso nesta ilha.";
			link.l1 = "Entendido, Barão. Então, daqui a três dias eu venho te buscar aqui. Boa sorte!";
			link.l1.go = "noel_6";
		break;
		
		case "noel_6":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "Patria_VisiterTortuga");
		break;
		
		case "noel_7":
			dialog.text = "Meu trabalho em Tortuga está feito, é hora de levantar âncora.";
			link.l1 = "Entendido, Barão. Vamos partir imediatamente.";
			link.l1.go = "noel_8";
		break;
		
		case "noel_8":
			DialogExit();
			Patria_VisiterTortugaSail();
		break;
		
		case "noel_9":
			dialog.text = "Yes, yes, we will definitely report this in Capsterville. The threat of such an important colony being conquered... unthinkable. I will personally ensure that Chevalier de Poincy takes strict and ruthless measures! Captain, I will remain on this island for a week; there are many plantations here, and it will take some time.";
			link.l1 = "Entendido, Barão. Vou te esperar perto do palácio do governador em sete dias. Aproveite e não se esforce demais!";
			link.l1.go = "noel_10";
		break;
		
		case "noel_10":
			DialogExit();
			DoQuestReloadToLocation("PortPax_town", "reload", "reload3", "Patria_VisiterPortPax");
		break;
		
		case "noel_11":
			dialog.text = "Aí está você, capitão. Meu trabalho em Hispaniola está feito, é hora de levantar âncora.";
			link.l1 = "Entendido, Barão. Partiremos imediatamente.";
			link.l1.go = "noel_12";
		break;
		
		case "noel_12":
			DialogExit();
			Patria_VisiterPortPaxSail();
		break;
		
		case "noel_13":
			dialog.text = "Capitão, essa ilha me parece familiar. Não é São Cristóvão?";
			link.l1 = "Sim, barão, exatamente. Já estamos quase lá.";
			link.l1.go = "noel_14";
		break;
		
		case "noel_14":
			dialog.text = "Quase chegando?! Não era pra gente passar por Saint-Martin também? Faz parte das colônias francesas.";
			link.l1 = "Você quer dizer Sint Maarten? É uma colônia holandesa, Monsieur Forget.";
			link.l1.go = "noel_15";
		break;
		
		case "noel_15":
			dialog.text = "É mesmo? Em Paris, isso era considerado francês. Como assim?";
			link.l1 = "Não faço ideia, Barão. Desde que pisei pela primeira vez no arquipélago, Sint Maarten sempre foi uma colônia holandesa. Talvez haja algo que eu não saiba. Você deveria considerar conversar com o Chevalier de Poincy sobre esse assunto.";
			link.l1.go = "noel_16";
		break;
		
		case "noel_16":
			dialog.text = "Está bem, capitão, que seja. De qualquer forma, já estamos quase em Capsterville.";
			link.l1 = "...";
			link.l1.go = "noel_17";
		break;
		
		case "noel_17":
			DialogExit();
			Island_SetReloadEnableGlobal("Nevis", true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			pchar.quest.Patria_visiter_fin.win_condition.l1 = "location";
			pchar.quest.Patria_visiter_fin.win_condition.l1.location = "Charles_Roomtownhall";
			pchar.quest.Patria_visiter_fin.function = "Patria_VisiterFin";
			pchar.questTemp.Patria = "epizode_2_return";
		break;
		
		case "noel_18":
			dialog.text = TimeGreeting()+", capitão. Que bom te ver. Fiquei sabendo da sua promoção, meus parabéns! Para ser sincero, você é mesmo um dos oficiais mais sensatos e talentosos a serviço de de Poincy.";
			link.l1 = "Obrigado, monsieur.";
			link.l1.go = "noel_19";
		break;
		
		case "noel_19":
			dialog.text = "Finalmente, só resta uma colônia, Saint-Martin. Para ser sincero, já estou cansado dessas viagens. Vou ficar feliz em terminar essa inspeção e começar a organizar a próxima campanha comercial das Índias Ocidentais Francesas. Estamos prontos para levantar âncora?";
			link.l1 = "Sim, Barão. Suba a bordo.";
			link.l1.go = "noel_20";
		break;
		
		case "noel_20":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBaron", 5.0);
		break;
		
		case "noel_21":
			dialog.text = "Capitão, pode me explicar o que acabou de acontecer? Isso significa guerra? Por que diabos quase fomos afundados pelos holandeses?";
			link.l1 = "Barão, eu mesmo não entendo nada! Deve ser algum tipo de mal-entendido, com certeza.";
			link.l1.go = "noel_22";
		break;
		
		case "noel_22":
			dialog.text = "Capitão, aposto que esse 'mal-entendido' tem nome! Peter Stuyvesant, o tal 'inquilino' de Saint-Martin e parceiro do nosso querido Chevalier de Poincy!";
			link.l1 = "Não faço ideia, Barão. É melhor irmos logo para Capsterville e informar o Governador-Geral sobre isso.";
			link.l1.go = "noel_23";
		break;
		
		case "noel_23":
			dialog.text = "Sem dúvida, é exatamente isso que vamos fazer! E eu vou exigir uma explicação! Eu sabia que alugar uma ilha para os holandeses era um grande erro! Vamos sair daqui o mais rápido possível, capitão, antes que alguém resolva nos perseguir!";
			link.l1 = "Exatamente, monsieur ...";
			link.l1.go = "noel_24";
		break;
		
		case "noel_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBack", 5.0);
		break;
		
		case "noel_25":
			dialog.text = "Monsieur, first let me congratulate you on your promotion! I eagerly supported Monseigneur de Poincy's decision to grant you the rank of Vice Admiral. You truly deserve this title! Now, I have recently returned from Saint-Martin. At the warehouses of Philipsburg, we conducted an inspection; all Dutch goods were confiscated and now belong to the treasury of France. You, as the commander of the operation, have been granted a share of the spoils. I agree with the Chevalier that this is only fair. Your goods have been transferred to the warehouse of the St. Christopher store, and you may collect them whenever you wish.";
			link.l1 = "Obrigado, Barão. Deixe as mercadorias lá por enquanto. Quando eu voltar de Curaçao, vou recolhê-las.";
			link.l1.go = "noel_26";
		break;
		
		case "noel_26":
			dialog.text = "Boa sorte na sua próxima campanha, Vice-Almirante! Tenho certeza de que voltará vitorioso e fará justiça ao punir aquele canalha do Stuyvesant.";
			link.l1 = "...";
			link.l1.go = "noel_27";
		break;
		
		case "noel_27":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_start";
			AddQuestRecord("Patria", "58");
			pchar.questTemp.Patria.GoodsSM = "true";
		break;
		
		case "noel_28":
			dialog.text = "Quem temos aqui! Vice-almirante Charles de Maure! Que bom te ver! O que te traz a Port-au-Prince?";
			link.l1 = "I'm pleased to meet you too, Baron. I'm here because of my duty; I had to pay monsieur Jeremy Deschamps du Mussaca a courtesy visit...";
			link.l1.go = "noel_29";
		break;
		
		case "noel_29":
			dialog.text = "Este encontro é realmente muito afortunado, pois estive esperando há muito tempo para conhecê-lo pessoalmente. Quero conversar com você, mas não aqui.";
			link.l1 = "Vamos para a taverna então, certo?";
			link.l1.go = "noel_30";
		break;
		
		case "noel_30":
			DialogExit();
			FreeSitLocator("PortPax_tavern", "sit_base1");
			DoQuestReloadToLocation("PortPax_tavern", "sit", "sit_base1", "Patria_CondotierTavern");
		break;
		
		case "noel_31":
			LAi_SetSitType(pchar);
			dialog.text = "Não há ouvidos indesejados aqui, podemos falar livremente...";
			link.l1 = "Estou ouvindo, Barão.";
			link.l1.go = "noel_32";
		break;
		
		case "noel_32":
			dialog.text = "Vice-Almirante, o senhor parece ser um homem de honra. Um oficial naval tão valente só poderia ser assim...";
			link.l1 = "Hum... Acho que não entendi direito o que você quis dizer, monsieur...";
			link.l1.go = "noel_33";
		break;
		
		case "noel_33":
			dialog.text = "Monsieur de Maure, queria lhe perguntar: o que acha do seu senhor, o Governador-Geral Philippe de Poincy?";
			link.l1 = "O dever de um oficial não é pensar em seu comandante, mas sim cumprir suas ordens.";
			link.l1.go = "noel_34";
		break;
		
		case "noel_34":
			dialog.text = "Ah, deixa disso, Vice-Almirante, não estamos no quartel, nem no salão do de Poincy. Vou falar direto: você não acha que o monsieur de Poincy... abusa do poder? Ainda não consigo esquecer como quase fomos afundados pelos canhões do Forte de Saint-Martin. Tenho certeza que a traição dos holandeses teve um motivo.";
			link.l1 = "Eles queriam conquistar a ilha.";
			link.l1.go = "noel_35";
		break;
		
		case "noel_35":
			dialog.text = "Sim, sim, mas por que exatamente no momento em que decidi inspecionar? Por que não um mês antes? Ou dois meses depois? Não acredito que isso tenha sido coincidência, monsenhor. Você não desconfia de nada? Nossas vidas estavam em jogo ali.";
			link.l1 = "Eu arrisco minha vida todos os dias, monsenhor Forget. Acho que o senhor entende isso...";
			link.l1.go = "noel_36";
		break;
		
		case "noel_36":
			dialog.text = "Seu coragem é indiscutível. Mas não era isso que eu queria dizer. Veja... Quando eu estava trabalhando em Saint-Martin, que foi libertada por você, ouvi várias vezes sussurros dos moradores sobre uma mina nas profundezas da ilha. Tentei perguntar sobre isso, mas todos fingiam ignorância. Eles tinham medo... Ficava claro que eu não parecia muito confiável, mas isso só aumentou minhas suspeitas: será que essa mina misteriosa é o motivo de tudo isso, Monsieur de Maure? Guerras são travadas por causa de ouro, não é mesmo?";
			link.l1 = "There are numerous mines in the archipelago. Most of them are exhausted and have become worthless. I know of one major operating gold mine; it is owned by the Spaniards on South Main. But I've never heard of gold mining on Saint-Martin.";
			link.l1.go = "noel_37";
		break;
		
		case "noel_37":
			dialog.text = "Você é habilidoso na arte da diplomacia, Vice-Almirante! Entendo: você não confia em mim. Sou novo por aqui... Monsieur de Maure, mas sou uma pessoa influente em Paris. O Ministro das Finanças é meu amigo próximo. Visito o Rei regularmente. Minha autoridade é muito maior que a de Philippe de Poincy, formalmente falando, é claro, pois aqui o Governador-Geral é a maior autoridade. Mas, para ser sincero, aqui nas colônias, só vale a lei do mais forte.";
			link.l1 = "Concordo totalmente com você nisso.";
			link.l1.go = "noel_38";
		break;
		
		case "noel_38":
			dialog.text = "Mas não em Paris. Lá, as pessoas mais influentes são o Rei e o Ministro das Finanças... meu grande amigo. Monsieur de Maure, você é um militar brilhante, mas acredito que Phillipe de Poincy está se aproveitando de você para fins pessoais. Você é inteligente, então deve ter suas suspeitas. Pode confiar em mim. Garanto total anonimato e o apoio das autoridades em Paris. Juro pelo meu título.";
			link.l1 = "***PERMANEÇA LEAL A POINCY***";
			link.l1.go = "noel_39"; // развилка
			link.l2 = "***FICAR DO LADO DO BARÃO FORGET***";
			link.l2.go = "noel_53";
		break;
		
		case "noel_39":
			dialog.text = "";
			link.l1 = "Eu entendo você, Monsieur Forger. Para alguém que não está acostumado com o jeito de pensar daqui, as ações de de Poincy podem realmente parecer estranhas. Quando cheguei ao Arquipélago pela primeira vez, fiquei genuinamente chocado com o que acontecia por aqui. Ainda me lembro das primeiras palavras que ouvi: 'Se você encontrar um navio espanhol desprotegido, pode tentar abordá-lo.' Traição, falsidade, engano – tudo isso está por toda parte. Pirataria, saques, roubos...";
			link.l1.go = "noel_40";
		break;
		
		case "noel_40":
			dialog.text = "";
			link.l1 = "Na Europa, estamos em paz com a Espanha. Mas aqui, somos inimigos ferozes. Os holandeses podem parecer amigáveis e inofensivos hoje, mas amanhã um funcionário da Companhia confisca suas mercadorias só porque de repente anunciaram que está proibido importar, mesmo que você não pudesse saber disso. O oficial inglês está praticando pirataria abertamente, afundando navios da Companhia, e a Companhia contrata um facínora que se disfarça de navio fantasma e apavora os comerciantes britânicos...";
			link.l1.go = "noel_41";
		break;
		
		case "noel_41":
			dialog.text = "";
			link.l1 = "In this wolf's den, we sometimes have to make strange decisions that may not be obvious to those unfamiliar with it all. And what seems suspicious to you is, in fact, the only correct course of action. It is difficult to sit on several chairs at once and still manage to send profits to the parent state. Chevalier de Poincy handles this perfectly; he is an experienced administrator and a visionary politician. Of course, he can make mistakes, but we all do at some point in our lives...";
			link.l1.go = "noel_42";
		break;
		
		case "noel_42":
			dialog.text = "";
			link.l1 = "E você precisa lidar com tudo e com todos. Com as ambições dos espanhóis, que acham que o Novo Mundo inteiro lhes pertence, com a ganância dos mercadores holandeses, com a frieza calculista e a brutalidade implacável dos ingleses. E até mesmo com os piratas.";
			link.l1.go = "noel_43";
		break;
		
		case "noel_43":
			dialog.text = "Com piratas?!";
			link.l1 = "Yes, you heard right. The Dutch and the British are actively cooperating with pirates... unofficially, of course. The Brethren of the Coast is a serious force that can challenge any nation in the region; they are in constant conflict with everyone they encounter, and no one is capable of stopping them. The only thing that makes them slightly less dangerous is the fact that they are scattered and act on their own behalf. Did you know that the former governor of Tortuga, Levasseur, actually created a state within a state, relying completely on pirates?";
			link.l1.go = "noel_44";
		break;
		
		case "noel_44":
			dialog.text = "Acho que já ouvi algo sobre isso...";
			link.l1 = "Alguns navios corsários poderosos que protegiam a ilha estavam sempre atracados no porto de Tortuga. Levasseur traiu a França, tornando-se uma espécie de autoridade local. E agora, depois da destruição do ninho de piratas em Tortuga junto com seu chefe, os piratas estão furiosos com os franceses...";
			link.l1.go = "noel_45";
		break;
		
		case "noel_45":
			dialog.text = "Não me diga!";
			link.l1 = "Sim. Tivemos que fazer isso, senão Tortuga teria sido perdida para nós, embora o resultado não tenha sido dos melhores. Agora, nenhum navio mercante francês pode se sentir seguro no Caribe. Os espanhóis, que também não têm acordos com os barões piratas, pelo menos contam com frotas de galeões robustos e navios de guerra poderosos, capazes de enfrentar os filibusteiros. Assim como os holandeses, com seus East Indiamen e xebecs. Mas, infelizmente, não podemos nos gabar disso. E os piratas franceses frequentemente assaltam os próprios mercadores franceses.";
			link.l1.go = "noel_46";
		break;
		
		case "noel_46":
			dialog.text = "Isto é loucura! Não há nenhum jeito de acabar com isso?";
			link.l1 = "Muitos já tentaram. No fim, em vez de lutar, eles compram lealdade com ouro. Dão cartas de corso, quero dizer.";
			link.l1.go = "noel_47";
		break;
		
		case "noel_47":
			dialog.text = "Hmm...";
			link.l1 = "So, speaking from experience, a French trading company here in the Archipelago would be a very bad idea. Do you understand now what difficulties you will have to face? How many bastards want to get their share of the income here? And they are not going to let go of it easily. And pirates, they are capable of unthinkable things; call them crazy if you want, but they almost always achieve their dirty goals. In order to protect merchant ships, you would have to maintain a massive military fleet, but will that be profitable from a financial standpoint?";
			link.l1.go = "noel_48";
		break;
		
		case "noel_48":
			dialog.text = "Mas os comerciantes franceses conseguem se virar por aqui de algum jeito?";
			link.l1 = "Exatamente, de certa forma. Principalmente agora, quando a fortaleza pirata de Levasseur em Tortuga foi tomada...";
			link.l1.go = "noel_49";
		break;
		
		case "noel_49":
			dialog.text = "Suas palavras estão de acordo com o que de Poincy disse.";
			link.l1 = "É a verdade. Aqui no arquipélago é assim mesmo, sempre foi.";
			link.l1.go = "noel_50";
		break;
		
		case "noel_50":
			dialog.text = "Você fala com tanta convicção. Nem eu sabia de tudo isso e, você tem razão: ainda não sei. Acho que minhas suspeitas sobre Poincy eram infundadas. Você me fez enxergar melhor. Agradeço, Vice-Almirante. Mas o ministro francês está contando com a criação da Companhia. O Rei precisa do dinheiro...";
			link.l1 = "I understand. But please take what I have just said into consideration; if the creation of the French West Indies is unavoidable, then please make sure that we have a strong military fleet to protect it.";
			link.l1.go = "noel_51";
		break;
		
		case "noel_51":
			dialog.text = "Sua graça é realmente admirável, Vice-Almirante! Que nobreza de espírito! Não me surpreende que tenha ficado aqui tanto tempo e não tenha se apressado em voltar para casa. Mas nos veremos de novo: voltarei aqui em meio ano. A Companhia Francesa de Comércio vai prosperar. E quanto aos piratas, acho que está exagerando um pouco. No fim das contas, temos navios de guerra e capitães corajosos, como você.";
			link.l1 = "I am sorry, Baron, but I am just one man, and besides me France has only one strong ship in the archipelago, 'Eclatant'. It won't be enough; we will lose far more than we will gain... Eh, whatever, it is what it is. I suppose we will think of something in the meantime... When will you be heading off to France?";
			link.l1.go = "noel_52";
		break;
		
		case "noel_52":
			dialog.text = "Em duas semanas voltarei para Saint Christopher, e de lá seguirei para casa. Monsieur de Poincy me deu um belo navio — uma brigue chamada 'Favory' — e um capitão excelente. O navio é rápido e o capitão tem experiência, mas, claro, eu me sentia mais segura com você. Lembro das nossas viagens pelo arquipélago, Vice-Almirante, foi realmente uma experiência maravilhosa.";
			link.l1 = "Obrigado pelas suas palavras gentis, Barão. Bem, acho que chegou a hora de nos despedirmos...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierToPirates");
		break;
		
		case "noel_53":
			dialog.text = "";
			link.l1 = "Aqui, todo mundo usa os outros. O Chevalier já me usava nos seus negócios muito antes de eu virar oficial da marinha.";
			link.l1.go = "noel_54";
		break;
		
		case "noel_54":
			dialog.text = "E isso é aceitável? O que você acha?";
			link.l1 = "Não. Mas o Chevalier não me deixou escolha: ou eu obedecia às ordens dele, ou meu irmão ficaria atrás das grades até o fim da vida, e o bom nome da minha família estaria arruinado.";
			link.l1.go = "noel_55";
		break;
		
		case "noel_55":
			dialog.text = "Horrível! Isso é puro terrorismo! Ele tinha algum motivo para fazer essas ameaças?";
			link.l1 = "Meu irmão teve o azar de ser o homem de confiança dele. Assim como eu sou agora.";
			link.l1.go = "noel_56";
		break;
		
		case "noel_56":
			dialog.text = "Onde está seu irmão agora?";
			link.l1 = "I managed to free him, but I lost him the very next day; he chose not to serve under anyone anymore.";
			link.l1.go = "noel_57";
		break;
		
		case "noel_57":
			dialog.text = "Eu sabia que Poincy não era quem dizia ser! Um lobo em pele de cordeiro! Vice-almirante, pode confiar em mim. Sou um homem de honra. E vou te libertar do jugo do seu 'patrão' se conseguirmos encontrar provas concretas das atividades criminosas dele. Você sabe de algo sobre essa história cansativa com Stuyvesant? Fale abertamente, e não se preocupe – você é apenas um militar, e tinha obrigação de cumprir suas ordens.";
			link.l1 = "Eu sei. De fato, há uma mina em Saint-Martin. Só que lá não extraem ouro, mas sal. Os espanhóis têm grande demanda por ele. Poincy não podia negociar diretamente com os espanhóis, então Stuyvesant atuava como intermediário.";
			link.l1.go = "noel_58";
		break;
		
		case "noel_58":
			dialog.text = "Então Poincy e Stuyvesant são sócios de negócios?";
			link.l1 = "Já foi. Depois que você demonstrou interesse em inspecionar o Saint-Martin, Stuyvesant resolveu tirar Poincy do jogo e ficar com todo o lucro da mina de sal para ele. Poincy não podia contar a ninguém... Mas Stuyvesant calculou mal, como podemos ver.";
			link.l1.go = "noel_59";
		break;
		
		case "noel_59":
			dialog.text = "Você acha que a mina ainda está funcionando?";
			link.l1 = "Tenho certeza disso. Parece que Poincy tem um novo aliado comercial agora. Nada menos que o próprio Coronel Doily.";
			link.l1.go = "noel_60";
		break;
		
		case "noel_60":
			dialog.text = "Podemos apresentar alguma prova ao ministério?";
			link.l1 = "Hmm. Durante o ataque à mina, que aliás foi feito pelos espanhóis, não pelos holandeses, capturamos o dono. Ele ainda está no meu navio. Você pode falar com ele. Existe a chance de que, em troca da liberdade, ele te conte muitas coisas interessantes.";
			link.l1.go = "noel_61";
		break;
		
		case "noel_61":
			dialog.text = "Vamos para o seu navio imediatamente. Mande levarem seu prisioneiro para sua cabine. Quero ter uma conversa com ele.";
			link.l1 = "Certo, vamos.";
			link.l1.go = "exit";
			npchar.greeting = "noel_4";
			AddDialogExitQuestFunction("Patria_CondotierToCabin");
		break;
		
		case "noel_62":
			dialog.text = "Ótimo, Vice-Almirante. Vou conversar com ele. Fique aqui, por favor.";
			link.l1 = "Claro...";
			link.l1.go = "noel_63";
		break;
		
		case "noel_63":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "rld", "aloc1", "", -1);
			DoQuestFunctionDelay("Patria_CondotierInCabinTalk", 3.0);
		break;
		
		case "noel_64":
			dialog.text = "Anotei todas as provas do seu prisioneiro, e ele assinou embaixo. Agora precisamos cumprir o que prometi a ele: quando houver uma boa oportunidade, pare em Cartagena e deixe-o desembarcar. Mas você ouviu tudo por si mesmo. Veja só que canalha é esse nosso Poincy! Alugou uma ilha para os holandeses, fez negócios ilegais lá e ainda deixou os espanhóis irem até lá para cuidar da mina! Tenho até medo de imaginar quanto dinheiro o tesouro do Rei está perdendo por causa do egoísmo dele!";
			link.l1 = "Será que essas provas vão ser suficientes para incriminar Poincy?";
			link.l1.go = "noel_65";
		break;
		
		case "noel_65":
			dialog.text = "Infelizmente, receio que não vá adiantar. As provas são muito importantes, mas não bastam. Mas não quero que você se envolva nisso tudo, por motivos que nós dois entendemos.";
			link.l1 = "O espanhol concordou em testemunhar diante da sua comissão quando ela chegar aqui.";
			link.l1.go = "noel_66";
		break;
		
		case "noel_66":
			dialog.text = "Isso só vai acontecer daqui a pelo menos seis meses, e quem sabe o que será desse espanhol, ou se vamos conseguir encontrá-lo depois em Cartagena... Precisamos de provas ainda mais valiosas. Ou seja – evidências de que a mina continua suas atividades secretas e ainda enche os bolsos do nosso querido governador-geral.";
			link.l1 = "Então você está sugerindo que a gente viaje para Saint-Martin?";
			link.l1.go = "noel_67";
		break;
		
		case "noel_67":
			dialog.text = "Sim. Você sabe como chegar até a mina?";
			link.l1 = "Eu aceito.";
			link.l1.go = "noel_68";
		break;
		
		case "noel_68":
			dialog.text = "Então, à noite, você e eu vamos entrar lá de fininho, bem quietos, pra ninguém ver a gente, e vamos descobrir o que está acontecendo lá.";
			link.l1 = "Muito bom.";
			link.l1.go = "noel_69";
		break;
		
		case "noel_69":
			dialog.text = "Mas e o Chevalier, hein? Agora entendo por que ele insinuou com tanta ousadia que estabelecer a Companhia Francesa de Comércio no Arquipélago seria pouco lucrativo... Claro, seria muito pouco lucrativo para ele!";
			link.l1 = "Já que agora somos aliados, Barão, vou lhe contar toda a verdade. Poincy me pediu... para convencê-lo a não criar a Companhia de Comércio aqui.";
			link.l1.go = "noel_70";
		break;
		
		case "noel_70":
			dialog.text = "Então é assim! Espero pelo menos que ele não tenha te pedido para me matar com uma espada ou uma pistola?";
			link.l1 = "Não. Você precisava ser convencido de outra forma.";
			link.l1.go = "noel_71";
		break;
		
		case "noel_71":
			dialog.text = "Poincy vai pagar por isso, mas agora precisamos zarpar imediatamente para Saint-Martin. O espanhol será entregue ao continente depois. Estamos partindo, Vice-Almirante!";
			link.l1 = "Vai parecer um pouco estranho você deixar a ilha no meu navio, não acha?";
			link.l1.go = "noel_72";
		break;
		
		case "noel_72":
			dialog.text = "Acho que não. Não era você quem devia me convencer? Pois foi exatamente isso que fez, haha! Sim, antes de zarpar para a Europa, vou dizer ao Chevalier que concordo com ele e que a Companhia de Comércio não será criada. Deixe-o viver na doce paz de uma mentira, por enquanto... Vamos!";
			link.l1 = "...";
			link.l1.go = "noel_73";
		break;
		
		case "noel_73":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierToSMartin", 5.0);
		break;
		
		case "noel_74":
			dialog.text = "Mostre o caminho, Vice-Almirante. A noite vai nos esconder com seu manto de escuridão.";
			link.l1 = "Me siga...";
			link.l1.go = "noel_75";
		break;
		
		case "noel_75":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.Patria_Condotier_inMine.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_inMine.win_condition.l1.location = "Location_reserve_03";
			pchar.quest.Patria_Condotier_inMine.function = "Patria_CondotierInMine";
		break;
		
		case "noel_76":
			dialog.text = "(sussurrando) Eu vi! Eu vi! Você viu? Casacas vermelhas! São soldados ingleses!";
			link.l1 = "Eu te disse – agora o Poincy faz negócios com o Coronel Doily.";
			link.l1.go = "noel_77";
		break;
		
		case "noel_77":
			dialog.text = "Você tinha razão. Já vi o suficiente. Agora vamos sair daqui o mais rápido possível antes que nos vejam!";
			link.l1 = "Combinado...";
			link.l1.go = "noel_78";
		break;
		
		case "noel_78":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload2_back", "Patria_CondotierToBeach", -1);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		case "noel_79":
			dialog.text = "Está vendo onde os 'projetos comerciais' do nosso querido Chevalier nos levaram? Os ingleses se comportam como donos numa ilha francesa! Isso é um absurdo!";
			link.l1 = "Precisamos sair daqui, ou alguém com certeza vai aparecer. Não podemos correr o risco de sermos reconhecidos.";
			link.l1.go = "noel_80";
		break;
		
		case "noel_80":
			dialog.text = "Vice-Almirante, estive pensando durante toda a nossa viagem para Saint-Martin, e tomei uma decisão: você pode marcar uma reunião com Peter Stuyvesant?";
			link.l1 = "Com Stuyvesant? Mas por quê?";
			link.l1.go = "noel_81";
		break;
		
		case "noel_81":
			dialog.text = "Um ex-sócio pode ter pistas importantes e até provas concretas do envolvimento dos Chevaliers. Tenho certeza de que Stuyvesant não está nada satisfeito com Poincy e vai querer se vingar, ainda mais depois desses últimos acontecimentos...";
			link.l1 = "Acredito que sim, Barão. Eu, pessoalmente, não teria coragem de ir ao palácio de Stuyvesant. Seria arriscado demais para mim, depois de tudo que fiz contra eles...";
			link.l1.go = "noel_82";
		break;
		
		case "noel_82":
			dialog.text = "I've already thought about it. We'll go to Curaçao, disembark in a bay far from the city, and send our captive Spaniard from the mine with a letter to Stuyvesant. I won't mention you there; instead, I'll inform him that I'm conducting an investigation against Poincy or something of the sort. I think the Dutchman will come to the rendezvous.";
			link.l1 = "Hmm. I don't think this is a good idea. Stuyvesant is no fool; he takes what he can, he might even try to imprison you and demand a huge ransom. But if we make him believe that all that happened was because of Poincy, he might side with us. Well, if you are so determined, let's give it a try.";
			link.l1.go = "noel_83";
		break;
		
		case "noel_83":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Shore40", "reload1_back", false);
			LocatorReloadEnterDisable("Shore40", "boat", false);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_LocationDisableOfficersGen("shore40", false);
			LAi_LocationDisableOfficersGen("Location_reserve_01", false);
			LAi_LocationDisableOfficersGen("Location_reserve_03", false);
			pchar.quest.Patria_CondotierCuracao.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCuracao.win_condition.l1.location = "shore22";
			pchar.quest.Patria_CondotierCuracao.function = "Patria_CondotierOnCuracao";
			AddQuestRecord("Patria", "81");
		break;
		
		case "noel_84":
			dialog.text = "Monsieur de Maure, por favor, perdoe minha tolice. Você estava certo sobre Stuyvesant. Eu devia ter imaginado que só um canalha ainda maior poderia ter desafiado de Poincy!";
			link.l1 = "Hah! Um milhão... Poincy queria um milhão, Stuyvesant quer um milhão... Parece que estamos andando em círculos...";
			link.l1.go = "noel_85";
		break;
		
		case "noel_85":
			dialog.text = "Do que está falando, Vice-Almirante?";
			link.l1 = "Quando cheguei ao Caribe, Poincy queria que eu pagasse um milhão como resgate pelo meu irmão.";
			link.l1.go = "noel_86";
		break;
		
		case "noel_86":
			dialog.text = "E você pagou tudo isso?";
			link.l1 = "Eu ganhei e eu paguei. Não em um mês, claro. Pra falar a verdade, eu era só um novato em terra firme naquela época. Mesmo assim, o Chevalier não deixou o Michel ir.";
			link.l1.go = "noel_87";
		break;
		
		case "noel_87":
			dialog.text = "E depois disso você se alistou para trabalhar para o Poincy? Sinceramente, não entendo você.";
			link.l1 = "Me alistei para servir à França e às pessoas que amo, não me curvo diante de ninguém além do rei.";
			link.l1.go = "noel_88";
		break;
		
		case "noel_88":
			dialog.text = "Com licença, Monsieur de Maure. Claro, você serve à França e ao Rei! Poincy vai responder por tudo! Inclusive por toda a dor que ele lhe causou.";
			link.l1 = "Muito bem, Barão, vou encontrar um milhão que posso dispensar. Suba a bordo... Eu vou resolver esse problema.";
			link.l1.go = "noel_89";
		break;
		
		case "noel_89":
			DialogExit();
			//chrDisableReloadToLocation = false; //17-add
			LAi_LocationFightDisable(&Locations[FindLocation("shore22")], false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 10.0);
			pchar.questTemp.Patria = "epizode_12_stivesant";
			AddQuestRecord("Patria", "83");
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Patria_CondotierStivesantTimeOver", 0, 0, 30, false); // таймер на месяц
		break;
		
		case "noel_90":
			dialog.text = "Queria falar comigo, Vice-Almirante?";
			link.l1 = "Sim. Tive uma reunião com Stuyvesant. Aqui está o livro-caixa dele.";
			link.l1.go = "noel_91";
		break;
		
		case "noel_91":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Não acredito! Hmm, deixa eu ver... (lendo)";
			link.l1 = "...";
			link.l1.go = "noel_92";
		break;
		
		case "noel_92":
			LAi_Fade("", "");
			dialog.text = "É isso! Nosso querido Chevalier está perdido. Assim que toda essa contabilidade chegar às mãos do Ministro das Finanças... Nem consigo imaginar o que vai acontecer com ele. Nem vamos precisar procurar o espanhol de Cartagena. Monsieur de Maure, você realmente pagou um milhão por este livro?";
			link.l1 = "Eu fiz isso. Se eu tentasse qualquer outra coisa, a França poderia perder suas colônias no Caribe por causa de uma guerra civil, que eu até poderia vencer, mas que tipo de almirante eu seria se lutasse contra o meu próprio povo.";
			link.l1.go = "noel_93";
		break;
		
		case "noel_93":
			dialog.text = "Você realmente faz jus ao seu nome. Eu juro a você, Vice-Almirante, que vai recuperar o que é seu. Tenho certeza de que encontraremos uma boa quantia de dinheiro nos cofres de Poincy e entre seus agiotas. Só peço que espere seis meses até eu voltar da Europa com uma comissão.";
			link.l1 = "E não se esqueça de trazer um regimento de soldados bem treinados e armados. E um navio como o 'Eclatant'. Também acredito que o capitão do 'Eclatant' ficará do nosso lado quando chegar a hora.";
			link.l1.go = "noel_94";
		break;
		
		case "noel_94":
			dialog.text = "Don't doubt it, he is also an honourable man. I have realised that moral values play a major role in making your own decisions. You did a great job in trusting me and exposing this state criminal. Now take me to Capsterville, where I will report to Poincy about the success of your mission – you managed to convince me, and I will abandon the idea of creating the trading company. Perhaps Poincy will even reward you for this – accept the reward with a clear conscience and do not worry about anything, you of all people deserve it. You will not be dragged into this, and your name will not be stained by the misdeeds of your superior; in fact, I will say all the best things about you when I meet with the king. Baron Forget is a man of honour and a man of his word.";
			link.l1 = "Fico feliz, Barão. Vamos partir!";
			link.l1.go = "noel_95";
		break;
		
		case "noel_95":
			DialogExit();
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;//открыть карту
			Island_SetReloadEnableGlobal("Curacao", true);
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
			pchar.questTemp.Patria = "epizode_12_baronwin";
			AddQuestRecord("Patria", "85");
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_CondotierBaron_win.function = "Patria_CondotierBaronWin";
		break;
		
		case "noel_96":
			dialog.text = "Então, Vice-Almirante, finalmente chegamos. Sua missão terminou, agora é comigo. Cuide dos seus próprios assuntos, defenda os interesses da França, como já fez antes. Daqui a uns seis meses, essa história desprezível vai chegar ao fim. Mandarei um mensageiro atrás de você quando for necessário. Adeus, Monsieur de Maure, tive muita sorte de encontrar um homem honrado aqui! O ministro e o Rei saberão de você, isso eu prometo. E só ouvirão o melhor.";
			link.l1 = "Obrigado, Barão. Boa viagem!";
			link.l1.go = "noel_97";
		break;
		
		case "noel_97":
			DialogExit();
			AddQuestRecord("Patria", "86");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		case "noel_98":
			dialog.text = "Fico feliz em vê-lo, Vice-Almirante. Estou aqui novamente, como prometido. E comigo está o Primeiro Assistente do Ministro das Finanças, Barão Olivier Bourdin.";
			link.l1 = "Onde está o Chevalier de Poincy?";
			link.l1.go = "noel_99";
		break;
		
		case "noel_99":
			dialog.text = "Onde deveria estar, na prisão. Ele foi preso e será levado para a França para investigação e julgamento. Dada a sua posição, certamente vai evitar a execução, mas não escapará de uma multa enorme, rebaixamento e, provavelmente, prisão.";
			link.l1 = "A prisão foi tranquila?";
			link.l1.go = "noel_100";
		break;
		
		case "noel_100":
			dialog.text = "Na verdade, não. O Chevalier tinha uma guarda inteira de soldados leais aqui na residência. Mas nós já estávamos preparados para esse tipo de situação com antecedência.";
			link.l1 = "Muito bem, parabéns, Barão! Talvez agora você vá lidar com a Companhia Francesa de Comércio?";
			link.l1.go = "noel_101";
		break;
		
		case "noel_101":
			dialog.text = "Eu? Sim. Sua Graça, Monsieur Bourdin, vai retornar à França junto com o Chevalier de Poincy. E você, Vice-Almirante, também deve esperar algumas mudanças. Agora você tem um novo cargo. Sua Graça vai lhe contar mais.";
			link.l1 = "...";
			link.l1.go = "noel_102";
		break;
		
		case "noel_102":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Finansist");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_103":
			dialog.text = "Monsieur de Maure! Espere um momento!";
			link.l1 = "Sim, Barão. Estou ouvindo.";
			link.l1.go = "noel_104";
		break;
		
		case "noel_104":
			dialog.text = "Quanto ao milhão que você pagou ao Stuyvesant... Eu não contei isso ao ministério, para... evitar perguntas, como por exemplo, como um oficial francês conseguiu tanto dinheiro. Isso poderia ter te prejudicado, já que provavelmente teriam pedido para você aumentar o tesouro do Rei com o seu próprio dinheiro.";
			link.l1 = "Entendi, obrigado.";
			link.l1.go = "noel_105";
		break;
		
		case "noel_105":
			dialog.text = "Todo o dinheiro encontrado com Poincy em Casterville foi confiscado pelo Barão Bourdin. Mas, ao que parece, Poincy também tinha um esconderijo que os agiotas ingleses estavam guardando para ele. Vou conversar com ele sobre devolver os investimentos e depois vou encontrar uma forma de te compensar.";
			link.l1 = "Receio que não será fácil para você tirar qualquer coisa das mãos dos agiotas ingleses.";
			link.l1.go = "noel_106";
		break;
		
		case "noel_106":
			dialog.text = "Concordo. Mas vamos trabalhar nisso, e eu vou te manter informado sobre os resultados.";
			link.l1 = "Como quiser.";
			link.l1.go = "noel_107";
		break;
		
		case "noel_107":
			dialog.text = "Vice-almirante, você não parece muito bem, ou é só impressão minha? Você acabou de receber o cargo mais alto nas colônias!";
			link.l1 = "Não, não, de jeito nenhum... É que tudo aconteceu tão de repente, e eu estou meio perdida.";
			link.l1.go = "noel_108";
		break;
		
		case "noel_108":
			dialog.text = "Não se preocupe. Você vai se acostumar com sua nova posição. Além disso, você foi um governador bem-sucedido em Saint-Martin por meio ano, então isso não será novidade para você.";
			link.l1 = "Ah, tenho certeza de que vou me acostumar. Já passei por situações piores aqui no Caribe. Acho que vou dar conta dessa também.";
			link.l1.go = "noel_109";
		break;
		
		case "noel_109":
			// belamour legendary edition -->
			dialog.text = "Pois bem. Além disso, tenho mais uma surpresa para você. Tenho certeza de que vai gostar. Mas antes, peço que volte para a residência. Acredito que alguém está nos esperando lá.";
			link.l1 = "Você me deixou intrigado, Monsieur Forget. Muito bem, vamos voltar.";
			link.l1.go = "noel_110";
		break;
		
		case "noel_110":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "ToEcliatonAward", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "noel_111":
			dialog.text = "Está tudo bem, Marquês. Um verdadeiro capitão deve sempre cuidar do seu navio primeiro, não é? Charles, você se lembra do Marquês Hubert Dassier, capitão do couraçado 'Eclatant'?";
			link.l1 = "É claro que me lembro! Se não fosse por ele, eu não estaria vivo hoje. As amizades mais fortes entre oficiais da marinha nascem em batalhas lutadas lado a lado. E o Monsieur Dassier mostrou ser um capitão incrivelmente experiente.";
			link.l1.go = "noel_112";
		break;
		
		case "noel_112":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_113":
			dialog.text = "Vice-Almirante, tenho a honra de informar o seguinte. Além de sua nomeação como Governador-Geral Interino das colônias francesas no arquipélago, também tratei da questão de sua nau capitânia.";
			link.l1 = "Nau capitânia?";
			link.l1.go = "noel_114";
		break;
		
		case "noel_114":
			dialog.text = "Exatamente. Pelo que sei, quando você entrou para o serviço da França, lhe foi entregue a corveta pesada 'Gryffondor'. É um navio excelente, sem dúvida, mas ainda assim é adequado apenas para um oficial, não para um vice-almirante e, agora, governador-geral. Você é o rosto da França aqui. E sua nau capitânia deve estar à altura. Por isso decidimos que o navio que travou suas primeiras batalhas aqui no Caribe será incorporado ao seu esquadrão...";
			link.l1 = "Monsieur Forget, o senhor está tentando dizer...";
			link.l1.go = "noel_115";
		break;
		
		case "noel_115":
			dialog.text = "A partir de agora, o orgulho da Marinha Francesa, o navio de guerra de 66 canhões 'Éclatant', está à sua disposição! Esta decisão foi aprovada pelo Rei!";
			link.l1 = "Mas Barão, eu não posso simplesmente aceitar...";
			link.l1.go = "noel_116";
		break;
		
		case "noel_116":
			dialog.text = "Você pode, Charles. Isso não está em discussão. Na França, o 'Eclatant' foi especialmente aprimorado para você, porque, como se descobriu, não há batalhas navais tão grandes no Caribe quanto na Europa, e por isso as exigências para cada navio são maiores. Aqui, tudo depende das características da embarcação e da experiência do seu capitão. O 'Eclatant' teve o casco reforçado, a capacidade de carga e o tamanho da tripulação aumentados, o velame foi levemente ajustado para permitir navegar mais rente ao vento, e todos os canhões foram substituídos por peças de calibre quarenta e dois, os canhões mais potentes que temos.";
			link.l1 = "Sim, agora este navio é realmente o senhor dos mares... Mas Monsieur Forget, o capitão deste navio é o Marquês Hubert Dassier. Eu não posso tirar isso dele...";
			link.l1.go = "noel_117";
		break;
		
		case "noel_117":
			dialog.text = "É só que ainda não te contei que o próprio Marquês manifestou um forte desejo de servir sob seu comando... Monsieur Dassier?";
			link.l1 = "...";
			link.l1.go = "noel_118";
		break;
		
		case "noel_118":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_119":
			dialog.text = "Sim, Monsieur Dassier, acredito que não vamos mais tomar o seu tempo.";
			link.l1 = "...";
			link.l1.go = "noel_120";
		break;
		
		case "noel_120":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			sld = characterFromId("Ecliaton_Cap");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "EcliatonAwardNoelTalk", -1);
		break;
		
		case "noel_121":
			dialog.text = "Entre nós, Charles, eu realmente aconselho que você mantenha o Marquês em seu serviço. Garanto que não vai encontrar um capitão tão experiente.";
			link.l1 = "Acredite em mim, Barão, tive a honra de presenciar isso pessoalmente durante os combates contra a Espanha e a Holanda. Monsieur Dassier é realmente um excelente oficial de combate, além de ser meu amigo.";
			link.l1.go = "noel_122";
		break;
		
		case "noel_122":
			dialog.text = "Bem, agora permita-me retirar-me, Vossa Graça, Governador-Geral! Não posso perder tempo: o trabalho de criar uma companhia comercial começa já no primeiro dia. Até breve!";
			link.l1 = "Boa sorte, Monsieur Forget. E sucesso nos seus negócios!";
			link.l1.go = "noel_123";
		break;
		
		case "noel_123":
			DialogExit();
			// ставим Эклятон после апгрейда в Европе
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_24";
			sld.DeckDialogNode = "ecliaton_cap_24";
			sld.Ship.Type = GenerateShipExt(SHIP_ECLIATON, true, sld);
			SetBaseShipData(sld);
			sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS42;
			UpgradeShipFull(sld);
			/* UpgradeShipParameter(sld, "SpeedRate");
			UpgradeShipParameter(sld, "TurnRate");
			UpgradeShipParameter(sld, "WindAgainstSpeed");
			UpgradeShipParameter(sld, "HP");
			UpgradeShipParameter(sld, "MaxCrew");
			sld.ship.HP = 11880; */
			sld.Ship.name = "Ecliaton";
			SetCrewQuantityFull(sld);
			AddCrewMorale(sld, 100);
			ChangeCrewExp(sld, "Sailors", 100);
			ChangeCrewExp(sld, "Cannoners", 100);
			ChangeCrewExp(sld, "Soldiers", 100);
			SetCharacterGoods(sld, GOOD_BALLS, 6000);
			SetCharacterGoods(sld, GOOD_GRAPES, 2000);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 2000);
			SetCharacterGoods(sld, GOOD_BOMBS, 5000);
			SetCharacterGoods(sld, GOOD_FOOD, 4000);
			SetCharacterGoods(sld, GOOD_POWDER, 12000);
			SetCharacterGoods(sld, GOOD_WEAPON, 900);
			SetCharacterGoods(sld, GOOD_MEDICAMENT, 900);
			SetCharacterGoods(sld, GOOD_RUM, 200);
			SetCharacterGoods(sld, GOOD_PLANKS, 100);
			SetCharacterGoods(sld, GOOD_SAILCLOTH, 100);
			Group_AddCharacter("Ecliaton_group", "Ecliaton_Cap");
			Group_SetGroupCommander("Ecliaton_group", "Ecliaton_Cap");
			Group_SetAddress("Ecliaton_group", "Nevis", "quest_ships", "quest_ship_1");
			Group_SetTaskNone("Ecliaton_group");
			Group_LockTask("Ecliaton_group");
			
			bDisableFastReload = false;//открыть переход
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Patria", "90");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.GenGovernor = "true"; // Шарль генерал-губернатор
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			DoQuestReloadToLocation("Charles_Town", "reload", "reload3", "OpenTheDoors");
		break;
		// <-- legendary edition
		
		case "noel_final":
			dialog.text = "Permita-me expressar minha mais sincera gratidão a você, Vice-Almirante! Você salvou minha vida ao me libertar daqueles malditos piratas. Agradeço a você, assim como a Philippe de Poincy. Preciso admitir, eu estava completamente enganado em meu julgamento sobre ele, e peço que me perdoe por isso. Você e o Chevalier estavam certos: a Companhia Francesa de Comércio vai ter muitos problemas aqui, e parece que só vamos perder dinheiro neste lugar. Só pessoas experientes como Poincy, e soldados tão corajosos quanto você, conseguem enfrentar esses lobos que vivem em cada ilha daqui. Preciso ir ao palácio, e depois partirei para a Europa o quanto antes, para esquecer este pesadelo.";
			link.l1 = "Fico feliz que tudo tenha acabado bem, Barão. Adeus!";
			link.l1.go = "noel_final_1";
		break;
		
		case "noel_final_1":
			DialogExit();
			AddQuestRecord("Patria", "76");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		// капитан Эклятона
		case "ecliaton_cap":
			dialog.text = TimeGreeting()+", monsieur. O que o traz ao convés do 'Eclatant'?";
			link.l1 = TimeGreeting()+", monsieur. Permita-me apresentar - Capitão Charles de Maure. Venho da parte do Governador-Geral das colônias francesas no Arquipélago, Chevalier de Poincy. Recebi ordens para incorporar seu navio à minha esquadra e colocá-lo sob meu comando. Aqui está a carta...";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) link.l1.go = "ecliaton_cap_1";
			else link.l1.go = "ecliaton_cap_no";
		break;
		
		case "ecliaton_cap_no":
			dialog.text = "Deve haver algum engano, monsieur. Você está a bordo de um navio de linha da marinha francesa, e eu só obedeço ordens de quem serve na Marinha Real. E você não parece ter nenhuma insígnia ou pertencer a essa frota. Talvez tenha confundido nosso navio com outro.";
			link.l1 = "Mas...";
			link.l1.go = "ecliaton_cap_no_1";
		break;
		
		case "ecliaton_cap_no_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_no_2";
		break;
		
		case "ecliaton_cap_no_2":
			if(IsUniformEquip())
			{
				dialog.text = "Hã, eu nem te reconheci nesse uniforme, Capitão. Muito bem, deixe-me ver sua carta, quero dar uma olhada no conteúdo.";
				link.l1 = "Aqui.";
				link.l1.go = "ecliaton_cap_1";
			}
			else
			{
				dialog.text = "Já discutimos tudo, monsieur...";
				link.l1 = "Hmm...";
				link.l1.go = "ecliaton_cap_no_1";
			}
		break;
		
		case "ecliaton_cap_1":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Bem, vejamos... (lendo) Interessante. Então, meu navio e eu ficaremos sob seu comando, Capitão de Maure?";
			link.l1 = "Essa é a ordem do Governador-Geral.";
			link.l1.go = "ecliaton_cap_2";
		break;
		
		case "ecliaton_cap_2":
			dialog.text = "Sim, sim, ordens não se discutem. Muito bem. Permita-me apresentar: sou o Marquês Hubert Dassier, Capitão do navio de linha francês de 66 canhões chamado 'Eclatant', junto desta tripulação bem treinada, e juro pela minha honra, é um dos melhores navios que a França já teve.";
			link.l1 = "Fico feliz em ouvir isso, pois a tarefa que nos foi dada pelo Governador-Geral vai exigir um bom conhecimento de navegação e artilharia.";
			link.l1.go = "ecliaton_cap_3";
		break;
		
		case "ecliaton_cap_3":
			dialog.text = "Você vai me contar os detalhes dessa operação que está por vir?";
			link.l1 = "Claro. Vamos nos mudar para a ilha espanhola de Trinidad, que fica a cerca de uma semana de viagem a sudeste daqui. Lançaremos um ataque surpresa contra o forte que protege a colônia de San Jose e o destruiremos completamente. Depois, negociaremos com os espanhóis a nossa compensação pelo recente ataque ao assentamento francês de Saint-Pierre.";
			link.l1.go = "ecliaton_cap_4";
		break;
		
		case "ecliaton_cap_4":
			dialog.text = "Entendi. Quando partiremos?";
			link.l1 = "O quanto antes. Temos que concluir essa tarefa em um mês, então temos tempo de sobra.";
			if (GetCompanionQuantity(pchar) > 4) link.l1.go = "ecliaton_cap_5_1";
			else link.l1.go = "ecliaton_cap_5";
		break;
		
		case "ecliaton_cap_5":
			dialog.text = "Certo, Capitão de Maure. Partiremos quando você ordenar.";
			link.l1 = "";
			link.l1.go = "ecliaton_cap_6";
		break;
		
		case "ecliaton_cap_6":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_AddEcliaton();
		break;
		
		case "ecliaton_cap_wait":
			dialog.text = "Tem alguma ordem, ou talvez alguma pergunta, Capitão de Maure?";
			link.l1 = "Ainda não...";
			link.l1.go = "ecliaton_cap_wait_1";
		break;
		
		case "ecliaton_cap_wait_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
		break;
		
		case "ecliaton_cap_5_1":
			dialog.text = "Mas, Capitão de Maure, primeiro você precisa reduzir o tamanho do seu esquadrão – meu navio não pode se juntar a você, ou o esquadrão ficará grande demais.";
			link.l1 = "Hm. Você tem razão. Vou deixar um navio aqui no porto.";
			link.l1.go = "ecliaton_cap_5_2";
		break;
		
		case "ecliaton_cap_5_2":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_5_3";
		break;
		
		case "ecliaton_cap_5_3":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Já reduziu seu esquadrão, monsieur?";
				link.l1 = "Sim, sim, eu me lembro, estou cuidando disso.";
				link.l1.go = "ecliaton_cap_5_2";
			}
			else
			{
				dialog.text = "Então, o 'Éclatant' está pronto para se juntar ao seu esquadrão, monsieur.";
				link.l1 = "Então vou para o meu navio, e você deve se preparar para zarpar.";
				link.l1.go = "ecliaton_cap_5";
			}
		break;
		
		case "ecliaton_cap_7":
			dialog.text = "Saudações, Comodoro. Teremos outra batalha pela frente?";
			link.l1 = "De fato, temos sim. Mais uma vez, vamos unir forças. Vamos atacar Philipsburg. O Governador-Geral nos incumbiu de expulsar os holandeses de Saint-Martin.";
			link.l1.go = "ecliaton_cap_9";
			link.l2 = "Temos sim, Capitão, mas só um pouco mais tarde. Eu aviso quando for a hora. O 'Eclatant' precisa estar pronto para zarpar a qualquer momento.";
			link.l2.go = "ecliaton_cap_8";
		break;
		
		case "ecliaton_cap_8":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_7";
			npchar.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "ecliaton_cap_9":
			dialog.text = "Está tudo claro. Vai ser uma missão difícil, monsenhor. Pelo que ouvi, o forte de Philipsburg tem muitos canhões.";
			link.l1 = "Tenho certeza disso, meu amigo, mas vamos dar um jeito. Prepare-se para zarpar, partiremos em breve.";
			link.l1.go = "ecliaton_cap_10";
		break;
		
		case "ecliaton_cap_10":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_BastionAddEcliaton();
		break;
		
		case "ecliaton_cap_11":
			dialog.text = "Que bom ver você no convés do 'Éclatant', Vice-Almirante! Quais são suas ordens?";
			link.l1 = "Prepare o 'Eclatant' para a partida. Primeiro, vamos navegar até a costa da Jamaica e, depois, junto com o esquadrão do Coronel D'Oyley, atacaremos Curaçao.";
			link.l1.go = "ecliaton_cap_13";
			link.l2 = "Haverá ordens, Capitão, mas depois. Avisarei quando for a hora. O 'Eclatant' deve estar pronto para zarpar a qualquer momento.";
			link.l2.go = "ecliaton_cap_12";
		break;
		
		case "ecliaton_cap_12":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_11";
			npchar.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "ecliaton_cap_13":
			dialog.text = "O 'Éclatant' e sua tripulação estão prontos, Vice-Almirante!";
			link.l1 = "Excelente. Então partimos imediatamente.";
			link.l1.go = "ecliaton_cap_14";
		break;
		
		case "ecliaton_cap_14":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_CuracaoAddEcliaton();
		break;
		
		// belamour legendary edition -->
		case "ecliaton_cap_15":
			dialog.text = "Com licença, senhores, não pude me juntar a vocês antes porque estava ocupado dando ordens no navio. Já achei que estava bastante atrasado, pois não os encontrei na residência, e por isso estava prestes a voltar para o navio...";
			link.l1 = "...";
			link.l1.go = "ecliaton_cap_16";
		break;
		
		case "ecliaton_cap_16":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_111";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_17":
			dialog.text = "Foi uma honra lutar ao seu lado, Monsieur de Maure! Preciso dizer que raramente encontro oficiais tão competentes e habilidosos quanto você. Tenho certeza de que eu mesmo não teria conseguido lidar com o forte daquela colônia espanhola em Trinidad tão rápido!";
			link.l1 = "Você se subestima, Monsieur Dassier. Nós resolvemos isso juntos.";
			link.l1.go = "ecliaton_cap_18";
		break;
		
		case "ecliaton_cap_18":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_113";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_19":
			dialog.text = "That's right. Although I am a marquis, I am still a sailor. For me, the Caribbean archipelago is new, unexplored, and full of adventure. Last time I was here for only a few months, but when I returned to Europe, I found myself missing this place. I would like to serve our Fatherland here. And you are a very talented and experienced captain; you have managed to win my sincere respect and my friendship. I would be honoured to serve under your command, Vice Admiral!";
			link.l1 = "Bem, eu não posso, e mais ainda! - Não quero recusar você, Monsieur Dassier!";
			link.l1.go = "ecliaton_cap_20";
		break;
		
		case "ecliaton_cap_20":
			dialog.text = "Eu também entendo que o Eclatant agora é sua nau capitânia, então vou compreender perfeitamente se decidir assumir o comando dela pessoalmente. Nesse caso, pode me deixar como seu oficial, me dar outro navio, ou simplesmente me dispensar – o Monsieur Forget gentilmente me prometeu que, nesse caso, me arranjaria um cargo digno na frota da Companhia Francesa das Índias Ocidentais.";
			link.l1 = "Posso te garantir, meu amigo, que não vai chegar a esse ponto. Você é um dos melhores capitães que já conheci, e com você ao meu lado seremos imparáveis.";
			link.l1.go = "ecliaton_cap_21";
		break;
		
		case "ecliaton_cap_21":
			dialog.text = "Obrigado por uma avaliação tão generosa das minhas habilidades. E mais uma coisa, Vice-Almirante. Não sei o tamanho da sua esquadra no momento, então, por precaução, vou esperar por você na ponte de comando do Éclatant, atracado no cais de Capsterville. Assim que decidir assumir o comando do navio, é só me avisar.";
			link.l1 = "Muito bem, Monsieur Dassier.";
			link.l1.go = "ecliaton_cap_22";
		break;
		
		case "ecliaton_cap_22":
			dialog.text = "Então peço permissão para me retirar. Vice-Almirante, Barão...";
			link.l1 = "Até logo, Monsieur Dassier.";
			link.l1.go = "ecliaton_cap_23";
		break;
		
		case "ecliaton_cap_23":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_119";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
	
		case "ecliaton_cap_24":
			dialog.text = "Vice-Almirante, seja bem-vindo a bordo. Gostaria de assumir o comando do Éclatant?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				
				link.l1 = "Ainda não, Marquês. Espere por ordens.";
				link.l1.go = "ecliaton_cap_24_1";
			}
			else
			{
				link.l1 = "Sim, Marquês, peço que se junte ao meu esquadrão. Este belo navio será um símbolo da grandeza e do poder da França no Caribe!";
				link.l1.go = "ecliaton_cap_25";
			}
		break;
		
		case "ecliaton_cap_24_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_24";
			npchar.DeckDialogNode = "ecliaton_cap_24";
		break;
		
		case "ecliaton_cap_25":
			dialog.text = "Não poderia concordar mais, excelência!";
			link.l1 = "... Agora, vamos ver do que realmente somos capazes!";
			link.l1.go = "ecliaton_cap_26";
		break;
		
		case "ecliaton_cap_26":
			DialogExit();
			DeleteAttribute(npchar, "ShipHideImmortal");
			SetCharacterRemovable(npchar, true);
			npchar.CompanionEnemyEnable = true; 
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			npchar.DeckDialogNode = "hired";
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.Payment = true;
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerWantToGo.DontGo = true;
			
			// удаление группы Эклятона, иначе клон-призрак
			pchar.quest.Patria_EcliatonDelGroup.win_condition.l1 = "ExitFromSea";
			pchar.quest.Patria_EcliatonDelGroup.function = "Patria_EcliatonDelGroup";
		break;
		// <-- legendary edition
		
		// д'Ойли на Антигуа
		case "doily":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "end" && colonies[FindColony("Pirates")].nation == PIRATE)
			{
				PlaySound("Voice\English\LE\Doily\Edvard_Doily_01.wav");
				dialog.text = "Oh, mas que encontro! Não é o próprio Capitão Charles de Maure?! Ouvi dizer que agora você tem um cargo na marinha francesa. Que surpresa, considerando para quem você estava, digamos, 'trabalhando' antes...";
				link.l1 = "Greetings, sir. Are you referring to the affair with Isla Tesoro? Oh, but it was not I who wrote the English laws, according to which the island was passed down to the heir of the explorer who discovered it, as per his will. So, I am not to blame for that; I only helped Miss Sharp to claim what was rightfully hers.";
				link.l1.go = "doily_1";
			}
			else
			{
				dialog.text = TimeGreeting()+", Capitão. Imagino que o representante da marinha francesa tenha chegado a Antígua com um objetivo importante em mente?";
				link.l1 = "De fato, senhor. Fui enviado aqui pelo Governador-Geral das colônias francesas, Philippe de Poincy. Saint Christopher está sitiada pelas esquadras navais espanholas e holandesas. O Chevalier pede ajuda a você e também a Sir Jonathan Fox. Aqui está a carta dele para o senhor, Coronel.";
				link.l1.go = "doily_3";
			}
		break;
		
		case "doily_1":
			dialog.text = "Fico curioso, Capitão, quanto dinheiro você ganhou com isso? Imagino que tenha sido bastante, já que conseguiu pagar pelos serviços do tal Loxley, que não são nada baratos. Tenho certeza de que os barões piratas te pagam uma parte regularmente para manter a ilha sob controle deles. Nós dois sabemos muito bem que Helen Sharp não passa de uma fachada.";
			link.l1 = "Coronel, nós dois também sabemos que os barões piratas agem, na maioria das vezes, em prol dos interesses da Inglaterra, não oficialmente, claro... Sem eles, seria bem difícil resistir à hegemonia espanhola na região, não concorda? Então, do ponto de vista dos políticos, o fato dos Irmãos da Costa terem mantido a ilha para si talvez tenha sido até mais lucrativo do que se Isla Tesoro tivesse se tornado uma base naval inglesa...";
			link.l1.go = "doily_2";
		break;
		
		case "doily_2":
			dialog.text = "Isso é discutivelmente verdade, Capitão, mas... seja como for. Imagino que você tenha vindo a Antígua com algum objetivo importante, não é? Talvez tenha a ver com o fato de que as relações entre dois antigos aliados — França e Holanda — pioraram consideravelmente?";
			link.l1 = "Muito bem. Fui enviado pelo governador-geral das colônias francesas, Philippe de Poincy. Saint Christopher está sitiada pelas marinhas espanhola e holandesa. O Chevalier pede a sua ajuda. Aqui está a carta dele para você, Coronel.";
			link.l1.go = "doily_3";
		break;
		
		case "doily_3":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Deixe-me ver... (lendo)";
			link.l1 = "";
			link.l1.go = "doily_3_1";
		break;
		
		case "doily_3_1":
			LAi_Fade("", "");
			dialog.text = "Hmm... very intriguing! Captain, your commander certainly knows how to pique my interest; it's not unusual for people to call him a cunning fox. We should have done this long ago, instead of trying to befriend the Dutch. We know very well what the Dutch Company and their Director stand for. Well then, I think in this situation we really shouldn't refuse to help the besieged Casterville, and we have more than enough troops to do so.\nWhat are the numbers and types of ships in their squadrons, Captain?";
			link.l1 = "Contei seis navios: um navio de linha de oitenta canhões de terceira classe e cinco navios de quarta classe. Eles também podem ter fragatas e galeões.";
			link.l1.go = "doily_4";
		break;
		
		case "doily_4":
			dialog.text = "Hum... Podemos enviar nosso esquadrão, composto por um navio de primeira classe com cem canhões, dois navios de quarta classe e uma fragata pesada, contra o deles.";
			if (!CheckAttribute(pchar, "questTemp.Patria.FailLugger"))
			{
				link.l1 = "Senhor, também temos um navio de guerra de 66 canhões, o 'Eclatant', navegando da costa de Guadalupe para ajudar na defesa de Saint-Christopher.";
				link.l1.go = "doily_5";
			}
			else
			{
				link.l1 = "Um navio de primeira linha será de grande ajuda na batalha que se aproxima.";
				link.l1.go = "doily_5_1";
			}
		break;
		
		case "doily_5":
			dialog.text = "Perfeito. Nesse caso, estamos bem fora do alcance dos canhões inimigos. A vitória será nossa.";
			link.l1 = "E não vamos esquecer do meu próprio navio, senhor. Eu não vou perder uma batalha dessas, nem pense nisso.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_5_1":
			dialog.text = "É verdade. Com a ajuda do forte de Casterville, a vitória será nossa.";
			link.l1 = "E não vamos esquecer do meu próprio navio, senhor. Eu não vou perder uma batalha dessas, nem pense nisso.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_6":
			dialog.text = "É claro, Monsieur de Maure. Seja como for, histórias sobre o seu talento na navegação são conhecidas em todo o arquipélago. Sua nau capitânia vai liderar o esquadrão.";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "Vou manter o resto dos navios do meu esquadrão, depois volto para você, e juntos correremos em auxílio dos sitiados.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "Vou preparar meu navio em breve, e partiremos rapidamente para ajudar os sitiados.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_7_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_7_2";
		break;
		
		case "doily_7_2":
			dialog.text = "Então, está pronto para partir?";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "Espere só um instante, senhor.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "Sim, senhor.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_8":
			dialog.text = "Então vamos começar, e que Deus nos ajude!";
			link.l1 = "...";
			link.l1.go = "doily_9";
		break;
		
		case "doily_9":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Patria", "42");
			Patria_SiegeAddEngSquadron();
		break;
		
		case "doily_10":
			dialog.text = "Tem mais alguma pergunta, senhor?";
			link.l1 = "Não, Coronel...";
			link.l1.go = "doily_11";
		break;
		
		case "doily_11":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			npchar.DeckDialogNode = "doily_10";
		break;
		
		case "doily_12":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_02.wav");
			dialog.text = "Pegue a carta para o Stuyvesant, senhor. Caso não saiba quem sou, permita-me apresentar: Coronel Edward Doily, governador de Port Royal e comandante desta expedição!\nPara ser sincero, tenho uma enorme vontade de arrasar o covil de bandidos conhecido como Willemstad. A mais vil, traiçoeira e desprezível organização do Caribe, chamada Companhia Holandesa das Índias Ocidentais, que acredita que todo o comércio do Arquipélago é direito exclusivo deles, e que contrata tipos como Jacob van Berg e outros piratas para capturar e afundar navios de mercadores ingleses...";
			link.l1 = "...";
			link.l1.go = "doily_13";
		break;
		
		case "doily_13":
			dialog.text = "Estou aqui para pôr fim a esses atos revoltantes e, para sua sorte, proponho uma solução diplomática. Por enquanto... Mas se o diretor desta organização abominável não aparecer para as negociações, vou acabar com o negócio dele. Depois que tomarmos a cidade, só deixarei cinzas para trás, e toda a pólvora que encontrarmos vamos colocar no porão do seu forte e explodir tudo. O mesmo destino espera suas plantações, e o próprio Stuyvesant vai acabar pendurado no mastro do meu navio...";
			link.l1 = "...";
			link.l1.go = "doily_14";
		break;
		
		case "doily_14":
			dialog.text = "Você vai precisar de mais de um ano para reconstruir sua colônia, e então não terá tempo para suas tramas e conspirações. Diga ao seu 'Senhor Diretor' tudo o que acabei de dizer, e não pense que isso são piadas ou promessas vazias. Minha paciência acabou, então é bom que você me entenda perfeitamente. Entendeu, Oficial?!";
			link.l1 = "Está tudo perfeitamente claro, Coronel.";
			link.l1.go = "doily_15";
		break;
		
		case "doily_15":
			dialog.text = "Ótimo. Então vá embora. Dou-lhe exatamente um dia para pensar nisso. Se depois de vinte e quatro horas Peter Stuyvesant não estiver aqui, parado como você está agora, que ele mesmo se culpe por isso.";
			link.l1 = "...";
			link.l1.go = "doily_16";
		break;
		
		case "doily_16":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_17";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "doily_17":
			dialog.text = "Acho que aquele cachorro sarnento do Stuyvesant vai aparecer por aqui. E se não vier – a culpa é só dele!";
			link.l1 = "...";
			link.l1.go = "doily_17_1";
		break;
		
		case "doily_17_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_17";
			AddQuestRecord("Patria", "63");
			Patria_CuracaoParlamenterGo();
		break;
		
		case "doily_18": // д'Ойли на берегу
			dialog.text = "You've done a good job with the fort, monsieur de Maure. Now we will approach the city gates by land. I will take the cannons from here; the path is shorter and easier, and you will disembark your company of marines at Santa Maria Cape and advance towards Willemstad. If you encounter any enemies on the way, you know what to do. No one can be left behind us.";
			link.l1 = "Claro, coronel. Vou encontrá-lo nos portões!";
			link.l1.go = "doily_19";
		break;
		
		case "doily_19":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Patria", "61");
			npchar.dialog.currentnode = "doily_10";
			Patria_CuracaoGotoMarch();
		break;
		
		case "doily_20":
			dialog.text = "Pois bem, parece que nossa missão terminou com grande sucesso. Parabéns, Capitão! Ah, me desculpe - Vice-Almirante! Vamos voltar para os navios. Vou mandar meus homens ficarem de guarda - aquele tolo do Stuyvesant provavelmente não vai se arriscar a nos atacar enquanto recuamos, mas não custa nada ter cautela.";
			link.l1 = "Tenho certeza de que os holandeses não ousariam quebrar um tratado recém-assinado.";
			link.l1.go = "doily_21";
		break;
		
		case "doily_21":
			dialog.text = "Foi um prazer trabalhar com você, Monsieur de Maure. Acho que nos veremos novamente em Port-Royal ou Capsterville.";
			link.l1 = "Sem dúvida, coronel. Agora, vamos avisar nossos homens para recuar.";
			link.l1.go = "doily_22";
		break;
		
		case "doily_22":
			DialogExit();
			AddQuestRecord("Patria", "64");
			Patria_CuracaoClear();
		break;
		
		case "doily_23":
			dialog.text = "Parece que os holandeses finalmente perceberam que não têm como se aproximar de nós pelo forte, naquele caminho estreito sob o fogo da nossa artilharia. E aqueles presos na cidade provavelmente não vão arriscar uma saída, a menos que estejam completamente loucos. Agora, vamos semear um pouco de pânico: vamos bombardear a cidade com nossos canhões. Os homens do meu navio vão ver isso e fingir que estão se preparando para desembarcar. Depois de uma ou duas horas, Stuyvesant vai se borrar de medo e estará pronto para enviar os emissários da trégua.";
			link.l1 = "Está tudo indo conforme o nosso plano, Coronel! Vamos nessa!";
			link.l1.go = "doily_24";
		break;
		
		case "doily_24":
			DialogExit();
			Patria_CuracaoTownBombing();
		break;
		
		// голландский парламентёр под стенами Виллемстада
		case "holoff":
			dialog.text = "Cheguei aqui para iniciar as negociações. Quais são suas exigências?";
			link.l1 = "Exigimos uma reunião com o Diretor da Companhia, Peter Stuyvesant. Especificamente, queremos discutir o fato de que, por negligência tanto da companhia quanto dele próprio, Willemstad está atualmente sob ameaça de destruição.";
			link.l1.go = "holoff_1";
		break;
		
		case "holoff_1":
			dialog.text = "Muito bem, vou contar isso ao senhor Stuyvesant, e nós vamos providenciar uma rota segura para a sua delegação entrar na cidade...";
			link.l1 = "E quanto a uma saída segura?";
			link.l1.go = "holoff_2";
		break;
		
		case "holoff_2":
			dialog.text = "Eu não entendo, senhor?";
			link.l1 = "Eu disse: você vai providenciar uma saída segura da cidade para nós? Não tenho certeza disso. Temo que o senhor Stuyvesant possa simplesmente decidir capturar nossos enviados. Por isso, convido o senhor Stuyvesant a vir até aqui para as negociações.";
			link.l1.go = "holoff_3";
		break;
		
		case "holoff_3":
			dialog.text = "Mas...";
			link.l1 = "Oficial, somos nós que ditamos as regras aqui. Sua frota foi destruída, a guarnição está isolada da cidade, e vamos romper as defesas de Willemstad como uma fragata atravessa um bote, se decidirmos atacar. Agora, você receberá uma carta para o senhor Stuyvesant, e vai entregá-la a ele junto com o nosso convite...";
			link.l1.go = "holoff_4";
		break;
		
		case "holoff_4": // перекидываем pchar на офицера и говорим с д'Ойли
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Curacao_parlamenter_1"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		// офицер-испанец на маяке Тринидада
		case "SanJoseSpanish":
			dialog.text = "Então, Capitão, você convocou os enviados da trégua porque queria impor suas exigências?";
			link.l1 = "Você está absolutamente certo, señor. Permita-me explicar brevemente o motivo da minha chegada a Trinidad – esta é a nossa resposta ao seu recente ataque a Saint-Pierre. Você causou grandes danos à cidade, e agora será obrigado a compensar por isso. O valor da compensação é de trezentos mil pesos. E não é tanto assim, considerando os atos desprezíveis que seus soldados cometeram na Martinica.";
			link.l1.go = "SanJoseSpanish_1";
		break;
		
		case "SanJoseSpanish_1":
			dialog.text = "Com licença, senhor, mas o que San Jose tem a ver com Saint-Pierre? Por que a nossa colônia tem que pagar?";
			link.l1 = "Porque os atacantes eram espanhóis, não holandeses ou ingleses. Então você enviará a conta para Providence, ao cuidado de Don de Mendoza, junto com minhas mais sinceras saudações. Como deve entender, caso se recusem a pagar a indenização, ordenarei que meus homens desembarquem, e então San Jose perderá muito mais. Tenho certeza de que o governador da sua colônia tomará a decisão certa. Vocês têm um dia para responder. Desejo tudo de bom a vocês, senhores.";
			link.l1.go = "SanJoseSpanish_2";
		break;
		
		case "SanJoseSpanish_2":
			DialogExit();
			npchar.dialog.currentnode = "SanJoseSpanish_3";
			Patria_SanJoseMayakSpanishGo();
		break;
		
		case "SanJoseSpanish_3":
			dialog.text = "";
			link.l1 = "Então, pelo que entendi, o governador tomou a decisão certa?";
			link.l1.go = "SanJoseSpanish_4";
		break;
		
		case "SanJoseSpanish_4":
			AddMoneyToCharacter(pchar, 300000);
			dialog.text = "Pegue seus trezentos mil e saia da nossa colônia.";
			link.l1 = "Excelente, senhores. Garanto a vocês – essa foi a melhor decisão. Espero que isso desanime Don de Mendosa e outros de atacarem nossas colônias. Não se esqueçam de enviar a mensagem para Providence e para ele pessoalmente. Desejo tudo de bom a vocês, cavalheiros.";
			link.l1.go = "SanJoseSpanish_5";
		break;
		
		case "SanJoseSpanish_5":
			DialogExit();
			Patria_SanJoseMayakSpanishFin();
		break;
		
		// вестовой на 5 задание
		case "fraofficer":
			dialog.text = "Capitão Charles de Maure, permita-me relatar: o Chevalier Philippe de Poincy deseja informar que o Barão Noel Forget está pronto para partir para Saint-Martin e o aguardará no cais.";
			link.l1 = "Excelente! Obrigado, monsieur.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			Patria_SanMartinSetBaron();
		break;
		
		case "fraofficer_2":
			dialog.text = "Capitão Charles de Maure! O Governador-Geral está chamando você agora mesmo. Um esquadrão inimigo formidável apareceu na costa de Saint-Christopher!";
			link.l1 = "Então não vamos perder tempo!";
			link.l1.go = "fraofficer_3";
		break;
		
		case "fraofficer_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			Patria_SiegeHovernor();
		break;
		
		// патруль у рудника
		case "engofficer":
			dialog.text = "Quem é você? O que está fazendo aqui?";
			link.l1 = "Uhh...";
			link.l1.go = "engofficer_1";
		break;
		
		case "engofficer_1":
			dialog.text = "Nenhum estranho pode entrar aqui! Quem são vocês, espiões? Vou levar vocês até o comandante, ele vai cuidar disso.";
			link.l1 = "Mas não podemos ir ao escritório do comandante...";
			link.l1.go = "engofficer_2";
		break;
		
		case "engofficer_2":
			dialog.text = "Se você não for por conta própria - vamos ter que te arrastar à força! Entregue suas armas!";
			link.l1 = "Sem acordo...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierBeachFight");
		break;
		
		// бывший управляющий рудника
		case "miner":
			dialog.text = "";
			link.l1 = "Então, está tudo claro?";
			link.l1.go = "miner_1";
		break;
		
		case "miner_1":
			dialog.text = "Sim, monsieur. A carta deve ser entregue pessoalmente ao senhor Peter Stuyvesant ou Mathias Beck.";
			link.l1 = "Tenho certeza de que você não terá dificuldade em encontrar um navio de Willemstad para Cartagena. Já lhe demos todo o dinheiro necessário para a viagem e hospedagem. E, se for preciso – você irá confirmar seus relatórios diante da comissão francesa daqui a seis meses?";
			link.l1.go = "miner_2";
		break;
		
		case "miner_2":
			dialog.text = "Monsieur, eu sou fiel à minha palavra.";
			link.l1 = "Muito bem. Então, desejo-lhe sorte. Este caminho leva a Willemstad, siga por ele. Não fica longe daqui.";
			link.l1.go = "miner_3";
		break;
		
		case "miner_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Patria_CondotierOnCuracaoWait", 15.0);
			AddQuestRecord("Patria", "82");
			ReleasePrisoner(npchar);
		break;
		
		// курьер в Капстервиль
		case "cureer":
			dialog.text = "Vice-Almirante Charles de Maure, certo?";
			link.l1 = "Exatamente. Com quem tenho a honra de falar?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "Tenho uma mensagem para você do Barão Noel Forget. Ele pediu que você vá ao palácio do governador em Casterville o quanto antes.";
			link.l1 = "Oh! Que notícia maravilhosa! Obrigado, partirei imediatamente!";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			Patria_EuropePrepare();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
		break;
		
		case "burden":
			dialog.text = "Saudações, Vice-Almirante. O Barão Forget me contou histórias sobre você. Muitas histórias. Ofereço meus mais sinceros agradecimentos pelo seu serviço leal e brilhante ao bem da França nas colônias, assim como pela sua ajuda em desmascarar as tramas do vigarista de Poincy. Agora, o Ministro das Finanças e eu vamos lidar com ele pessoalmente, e você assumirá o lugar do seu antigo comandante. Pelo menos, por enquanto.";
			link.l1 = "Mas...";
			link.l1.go = "burden_1";
		break;
		
		case "burden_1":
			dialog.text = "Sem 'mas', vice-almirante! Esta decisão já foi tomada e aprovada pelo Rei. Tenho aqui uma ordem assinada por ele pessoalmente, nomeando você como Governador-Geral de fato das colônias francesas no Arquipélago. Não temos candidatos melhores para este cargo. Sua experiência excepcional em combate, seu conhecimento da região e das pessoas responsáveis por tudo aqui, suas habilidades e talentos são dignos desta posição tão alta e respeitável. Se me permite ser sincero, espero que, com o tempo, você seja nomeado novamente para este cargo, mas sem o 'de fato'.";
			link.l1 = "Mas eu sonhava em voltar para Paris...";
			link.l1.go = "burden_2";
		break;
		
		case "burden_2":
			dialog.text = "A França precisa de você aqui! O Ministro das Finanças está montando uma marinha na Europa neste exato momento, e nossa presença aqui no Arquipélago também não passará despercebida. Sua principal missão será fortalecer e fortificar as colônias e aumentar o poder militar da nossa frota, enquanto o Barão Forget e a Companhia Francesa das Índias Ocidentais vão se concentrar no comércio e no desenvolvimento interno! E quem mais, senão você, pode ajudar a preparar a marinha francesa?\nEntão, mãos à obra, Governador-Geral! Eu sei que você não gosta de ficar trancado numa sala o dia todo, mas sua tarefa nem exige isso!";
			link.l1 = "Imediatamente, Vossa Graça! Ordens não se discutem!";
			link.l1.go = "burden_3";
		break;
		
		case "burden_3":
			dialog.text = "Fico feliz que você tenha me entendido corretamente. Também gostaria de pedir que faça uma visita ao Chevalier de Poincy: ele fez questão de conhecê-lo. Não podemos negar esse prazer a ele antes de sua partida para Paris, não é? Você o encontrará na prisão.";
			link.l1 = "Muito bem, sua Graça...";
			link.l1.go = "burden_4";
		break;
		
		case "burden_4":
			DialogExit();
			DoQuestReloadToLocation("Charles_prison", "goto", "goto19", "Patria_EuropePuancieInPrison");
		break;
		
		// Портной Пуанси Xenon
		case "Tailor":
			dialog.text = "...vai atrasar, entendeu? Eu pedi esses materiais há vários meses!";
			link.l1 = "...";
			link.l1.go = "Tailor_01";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_01":
			DialogExit();
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_02":
			dialog.text = "E como eles decidiram o que carregar no primeiro navio e o que colocar no segundo?! Eu não sou apenas uma costureira do fim do mundo – eu até tenho uma encomenda do governador-geral, Sua Excelência Chevalier de Poincy!";
			link.l1 = "...";
			link.l1.go = "Tailor_03";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_03":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor_02";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_04":
			dialog.text = "Bem, o que mais posso fazer agora... Vou esperar. Mas saiba de uma coisa: não vou me responsabilizar por pedidos não cumpridos!";
			link.l1 = "Saudações. Vejo que você está com problemas?";
			link.l1.go = "Tailor_05";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_05":
			dialog.text = "Problemas? Isso é pouco! Ah, acho que te reconheço... Você é o novo vice-almirante, certo?";
			link.l1 = "Rápido para entender. Isso mesmo, diante de você está o segundo homem nas colônias francesas, Vice-Almirante da frota francesa, Charles de Maure.";
			link.l1.go = "Tailor_06";
			link.l2 = "Deixe essas formalidades de lado, não estamos a bordo de um navio. E não se preocupe, não vou chamar os guardas só porque você não me reconheceu de imediato. Pode me chamar de Charles de Maure.";
			link.l2.go = "Tailor_07";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tailor_06":
			AddCharacterExpToSkill(pchar, "Leadership", 300);//харизма
			dialog.text = "Vossa Excelência, por favor, me perdoe por não tê-lo reconhecido de imediato! Sim, está certo, encontrei circunstâncias imprevistas.";
			link.l1 = "E quais seriam essas circunstâncias? Pelo que entendi, eles não trouxeram nenhum material de Paris para você?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_07":
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			dialog.text = "Oh, muito obrigado. Você tem razão, acabei me deparando com situações inesperadas, por isso não percebi de imediato quem estava na minha frente.";
			link.l1 = "E que circunstâncias seriam essas? Pelo que entendi, eles não trouxeram nenhum material de Paris para você?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_08":
			dialog.text = "Sim, está certo. Eu os encomendei há vários meses. O governador assinou a ordem para sua nomeação naquela época e fez questão de que eu preparasse todo o material necessário para o uniforme de um novo almirante, confiante de que seria aprovado na capital.";
			link.l1 = "E os materiais não foram entregues, presumo?";
			link.l1.go = "Tailor_09";
		break;
		
		case "Tailor_09":
			dialog.text = "Imagine só! Expliquei o quanto era importante, fiz o pedido... Mas eles têm entregas mais urgentes para cuidar! O que eu faço? Faço meus pedidos com um ano de antecedência, torcendo para que eles se dignem a me trazer os materiais?";
			link.l1 = "O que exatamente está faltando para você? Talvez possa ser encontrado no Caribe?";
			link.l1.go = "Tailor_10";
		break;
		
		case "Tailor_10":
			dialog.text = "Mesmo que seja possível, não faço ideia de onde... Você não vai encontrar bons materiais por aqui. Mas... Eu poderia usar seu antigo casaco de oficial como base, se você permitir. Provavelmente não vai precisar dele depois que tiver o uniforme de almirante, certo?";
			link.l1 = "Se eu tiver um uniforme de almirante, claro que não vou precisar de uma jaqueta comum de oficial. O que mais?";
			link.l1.go = "Tailor_11";
		break;
		
		case "Tailor_11":
			dialog.text = "Preciso encontrar abotoaduras e uma gola para o uniforme. Normalmente, eu as encomendo diretamente de oficinas parisienses. Mesmo que sejam bem simples, consigo ajustá-las e deixá-las com um visual mais apresentável. Mas, nesse caso, vou precisar de mais delas...";
			link.l1 = "Já que não existem ateliês parisienses no Caribe, vou conseguir para você um lote inteiro de roupas locais com colarinhos e punhos removíveis. O que mais?";
			link.l1.go = "Tailor_12";
		break;
		
		case "Tailor_12":
			dialog.text = "Para os toques finais, preciso de tecidos de altíssima qualidade. Tenho uma fiandeira que consegue fazer esse tecido até de fibra grossa. Mas, para isso, preciso do material – de preferência algodão. Um fardo já será mais do que suficiente.";
			link.l1 = "Isso também pode ser resolvido. O que vem agora?";
			link.l1.go = "Tailor_13";
		break;
		
		case "Tailor_13":
			dialog.text = "Era para entregarem um tricórnio de almirante vindo de Paris, mas eu mesmo posso fazer um se tiver os materiais. Embora o seu tricórnio fosse para ser de tecido, o couro seria melhor para os ventos salgados e o sol escaldante do Caribe. Duraria muito mais.";
			link.l1 = "I'll get you the leather; don't worry. I won't even have to chase bulls through the jungles of Espanola. Is that all?";
			link.l1.go = "Tailor_14";
		break;
		
		case "Tailor_14":
			dialog.text = "Eles também deveriam entregar seda de primeira qualidade de Lyon. É leve, respirável, absorve a umidade com facilidade e seca ainda mais rápido. E o mais importante, não estica e mantém o formato.";
			link.l1 = "Sim, eu entendo de que seda você está falando. Mas pode ser mais difícil conseguir isso nas colônias.";
			link.l1.go = "Tailor_15";
		break;
		
		case "Tailor_15":
			dialog.text = "Isso é tudo quanto aos materiais. Também ouvi dizer que você recebeu a mais alta condecoração da França... A Ordem de Saint Louis não deve ser usada como um enfeite qualquer no cinto. Ela tem o seu lugar. Então, por favor, traga-a para mim, e eu vou costurá-la como deve ser.";
			link.l1 = "Certo, vou levar também. Só não perca isso!";
			link.l1.go = "Tailor_16";
		break;
		
		case "Tailor_16":
			dialog.text = "De jeito nenhum! Vou protegê-lo com a minha vida!";
			link.l1 = "Certo então. Se for só isso, vou buscar os materiais.";
			link.l1.go = "Tailor_17";
		break;
		
		case "Tailor_17":
			dialog.text = "Tem mais uma coisa... Minhas ferramentas de costura ficaram inutilizáveis. Pedi novas de Paris, mas infelizmente... Se você conseguir todos os materiais necessários e puder me emprestar as ferramentas, se tiver – só me empreste, depois eu compro outras! – eu começo a costurar na hora.";
			link.l1 = "Bem, o que posso fazer? Vou trazer tudo o que você precisar. Onde posso te encontrar? Você não vai ficar me esperando na capitania do porto, vai?";
			link.l1.go = "Tailor_18";
		break;
		
		case "Tailor_18":
			dialog.text = "Minha oficina fica no prédio bem ao lado do cais - quando você desembarcar, estará à sua direita.";
			link.l1 = "Fechado. Vou conseguir os materiais para você.";
			link.l1.go = "Tailor_19";
		break;
		
		case "Tailor_19":
			DialogExit();
			AddQuestRecord("Patria", "65_1");
			chrDisableReloadToLocation = false;
			ChangeCharacterAddressGroup(npchar, "Charles_houseS3", "barmen", "Stay");
			npchar.dialog.currentnode = "Tailor_20";
			LAi_SetOwnerType(npchar);
			pchar.questTemp.PatriaTailor = true;
		break;
		
		case "Tailor_20":
			dialog.text = "Saudações, Vice-Almirante! Trouxe tudo o que precisa para o seu novo uniforme?";
			link.l1 = "Ainda não, não tive tempo. Espera aí, vou pegar tudo.";
			link.l1.go = "Tailor_20_exit";
			if(CheckCoatItems())
			{
				link.l2 = "Sim, eu trouxe tudo. Aqui está meu velho casaco, a Ordem e as ferramentas de alfaiataria. O resto dos materiais, meus marinheiros vão levar para sua oficina em breve.";
				link.l2.go = "Tailor_21";
			}
		break;
		
		case "Tailor_20_exit":
			npchar.dialog.currentnode = "Tailor_20";
			DialogExit();
		break;
		
		case "Tailor_21":
			RemoveItems(pchar, "talisman9", 1);
			RemoveItems(pchar, "suit1", 1);
			RemoveItems(pchar, "tailor_tool", 1);
			RemoveCharacterGoods(pchar, GOOD_CLOTHES, 1);
			RemoveCharacterGoods(pchar, GOOD_COTTON, 1);
			RemoveCharacterGoods(pchar, GOOD_LEATHER, 1);
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			dialog.text = "Maravilhoso! Para ser sincero, não achei que você conseguiria conseguir tudo isso. Estou acostumado a trabalhar só com tecidos de Paris, mas parece que você consegue fazer ternos bem decentes com materiais locais.";
			link.l1 = "Quanto tempo até meu novo uniforme ficar pronto?";
			link.l1.go = "Tailor_22";
		break;
		
		case "Tailor_22":
			dialog.text = "Normalmente, leva pelo menos uma semana, mas considerando que os clientes são os dois oficiais de mais alta patente da França nas colônias... Volte em três dias, e eu prometo que tudo estará pronto da melhor forma possível! Não precisamos tirar medidas, vou fazer tudo com base na sua jaqueta antiga.";
			link.l1 = "Ótimo! Então volto em três dias.";
			link.l1.go = "Tailor_23";
		break;
		
		case "Tailor_23":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
			SetFunctionTimerCondition("Patria_Tailor_Done", 0, 0, 3, false);
		break;
		
		case "Tailor_24":
			if(CheckAttribute(pchar,"questTemp.PatriaTailorDone"))
			{
				dialog.text = "Vice-Almirante! É um prazer vê-lo!";
				link.l1 = "Bem, vim buscar o novo uniforme, como combinamos.";
				link.l1.go = "Tailor_27";
			}
			else
			{
				dialog.text = "Saudações, Vice-Almirante! Peço desculpas, mas seu uniforme ainda não está pronto.";
				link.l1 = "Bem, posso pelo menos dar uma olhadinha no que está acontecendo?";
				link.l1.go = "Tailor_25";
			}
		break;
		
		case "Tailor_25":
			dialog.text = "Não, não! Agora mesmo, está completamente fora de condições, e eu não quero te decepcionar. Por favor, tenha um pouco de paciência.";
			link.l1 = "Ok, eu vou esperar.";
			link.l1.go = "Tailor_26";
		break;
		
		case "Tailor_26":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
		break;
		
		case "Tailor_27":
			dialog.text = "Sim, claro! Preciso lhe dizer, ficou tão bom quanto os feitos em Paris! Você tinha razão, mesmo nas colônias dá para encontrar material de qualidade, se souber onde procurar. Só um instante. Aqui está! Por favor, examine e experimente.";
			link.l1 = "Obrigado. Excelente qualidade! E ficou perfeito.";
			link.l1.go = "Tailor_28";
		break;
		
		case "Tailor_28":
			dialog.text = "Não só ficou ótimo! Você pode usar isso com orgulho como Vice-Almirante da França nas colônias! E sua Ordem, como prometi, agora está no lugar certo, e não mais pendurada no seu cinto.";
			link.l1 = "Bom trabalho! Quando encontrar o Chevalier de Poincy, pode dizer a ele que estou satisfeito.";
			link.l1.go = "Tailor_29";
		break;
		
		case "Tailor_29":
			dialog.text = "Com certeza vou contar pra ele! Que o uniforme lhe sirva bem! Boa sorte!";
			link.l1 = "Obrigado! Adeus.";
			link.l1.go = "Tailor_30";
		break;
		
		case "Tailor_30":
			DialogExit();
			npchar.dialog.currentnode = "first time";
			npchar.lifeday = 0;
			DeleteAttribute(pchar,"questTemp.PatriaTailorDone");
			DeleteAttribute(pchar, "questTemp.PatriaTailor");
			//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			GiveItem2Character(pchar, "suit5");
			EquipCharacterbyItem(pchar, "suit5");
			GiveItem2Character(pchar, "hat5");
			EquipCharacterbyItem(pchar, "hat5");
			AddItems(pchar, "tailor_tool", 1);
			Log_Info("You have received the Vice-Admiral's uniform!");
			AddQuestRecord("Patria", "65_2");
		break;
		
		//belamour legendary edition
		case "BladeUpg":
			string sItem, attrL, attrB;
			ref rItem;
			aref arItems; 
			int i, n, iItemsNum;
			dialog.text = "Qual lâmina você gostaria de aprimorar?";
			
			i = 1;
			makearef(arItems, pchar.items);
			iItemsNum = GetAttributesNum(arItems);
			for(n=0; n<iItemsNum; n++)
			{
				sItem = GetAttributeName(GetAttributeN(arItems, n));
				rItem = ItemsFromID(sItem);
				if(!CheckAttribute(rItem, "groupID")) continue;
				if(rItem.groupID != BLADE_ITEM_TYPE) continue;
				if(rItem.price == 0) continue;
				if(IsEquipCharacterByItem(pchar, rItem.id)) continue;
				if(sItem != "" && rItem.groupID == BLADE_ITEM_TYPE) 
				{
					attrL = "l" + i;
					Link.(attrL) = GetItemName(rItem) + ": Attack - " + FloatToString(stf(rItem.attack),1) + ", balance - " + FloatToString(stf(rItem.Balance),1) + ", weight - " + FloatToString(stf(rItem.Weight),1);
					Link.(attrL).go = "bladeindex_"+GetItemIndex(rItem.id);
					i++;
				}
			}
			
			link.l500 = "Mudei de ideia";
			link.l500.go = "exit";
		break;
	}
} 

bool CheckCoatItems()
{
	if(GetSquadronGoods(pchar, GOOD_CLOTHES) > 0
	&& GetSquadronGoods(pchar, GOOD_COTTON) > 0
	&& GetSquadronGoods(pchar, GOOD_LEATHER) > 0
	&& GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0
	&& GetCharacterFreeItem(pchar, "talisman9") > 0
	&& GetCharacterFreeItem(pchar, "suit1") > 0
	&& GetCharacterFreeItem(pchar, "tailor_tool") > 0)
	return true;
	
	return false;
}
